/*
 * rays.c - Ray and sphere intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.h"
#include "rays.h"
#include "vectors.h"

// TODO: Test if using `vec3Mag` and `vec3Norm` is faster than the `Vec4` variants

// Intersection collection constructor.
// If the allocation fails, `abort()` is called
void intersectionsCreate(Intersections *dest, const size_t size)
{
    if (size != 0)
    {
        dest->elem = malloc(sizeof(Intersection[size]));
        if (dest->elem == NULL)
        {
            abort();
        }
        dest->size = size;
        dest->capacity = size;
    }
    else
    {
        dest->elem = NULL;
        dest->size = 0;
        dest->capacity = 0;
    }
}

// Intersection collection copy constructor.
// If the allocation fails, size is set to zero.
void intersectionsCopy(Intersections *dest, const Intersections *src)
{
    if (src->size == 0)
    {
        dest->size = 0;
        dest->capacity = 0;
        dest->elem = NULL;
        return;
    }
    dest->elem = malloc(sizeof(Intersection[src->size]));
    if (dest->elem == NULL)
    {
        abort();
    }
    else
    {
        dest->size = src->size;
        dest->capacity = src->capacity;
        memcpy(dest->elem, src->elem, sizeof(Intersection[src->size]));
    }
    intersectionsSort(dest);
}

// Intersection collection destructor
void intersectionsDestroy(Intersections *dest)
{
    free(dest->elem);
    dest->capacity = 0;
    dest->size = 0;
    dest->elem = NULL;
}

// Compares two intersection elements
int intersectionCmp(const void *a, const void *b)
{
    if (fabs(((const Intersection *)a)->t - ((const Intersection *)b)->t) <= MAT_EPSILON)
    {
        return 0;
    }
    else if (((const Intersection *)a)->t > ((const Intersection *)b)->t)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Sorts an intersection collection
void intersectionsSort(Intersections *dest)
{
    qsort(dest->elem, dest->size, sizeof(Intersection), intersectionCmp);
}

// Resizes the size of the intersection collection.
// Info: Actual allocation cannot shrink
void intersectionsResize(Intersections *dest, const size_t size)
{
    dest->size = size;
    if (size > dest->capacity)
    {
        if (dest->capacity != 0)
        {
            while (dest->capacity < size)
            {
                // TOOD: Make this more efficient using bitshifts
                dest->capacity *= 2;
            }
        }
        else
        {
            dest->capacity = size;
        }
        dest->elem = realloc(dest->elem, sizeof(Intersection[dest->capacity]));
        if (dest->elem == NULL)
        {
            abort();
        }
    }
}

// Inserts an element at the end of the collection
void intersectionsPush(Intersections *dest, const Intersection intersection)
{
    intersectionsResize(dest, dest->size + 1);
    dest->elem[dest->size - 1] = intersection;
}

// Removes an element at the end of the collection and returns it
Intersection intersectionPop(Intersections *dest)
{
    dest->size--;
    return dest->elem[dest->size];
}

// Returns a point on the ray
Vec4 rayPos(const Ray ray, const double t)
{
    return vec4Add(ray.origin, vec4Mul(ray.direction, t));
}

// Returns a ray that has been transformed by a transformation matrix
Ray rayTransform(Ray ray, const Mat4 mat)
{
    ray.origin = mat4VecMul(mat, ray.origin);
    ray.direction = mat4VecMul(mat, ray.direction);
    return ray;
}

// Returns a ray from the camera passing through the chosen pixel on the canvas
Ray rayPixel(const Camera camera, const size_t x, const size_t y)
{
    const double xOffset = (x + 0.5) * camera.pixelSize;
    const double yOffset = (y + 0.5) * camera.pixelSize;
    const double worldX = camera.halfWidth - xOffset;
    const double worldY = camera.halfHeight - yOffset;
    const Vec4 pixel = mat4VecMul(camera.transformInv, point(worldX, worldY, -1));
    const Vec4 origin = mat4VecMul(camera.transformInv, point(0, 0, 0));
    return (Ray){origin, vec4Norm(vec4Sub(pixel, origin))};
}

// Returns the intersection between a shape and a ray
Intersections intersect(const Shape shape, Ray ray)
{
    ray = rayTransform(ray, shape.transformInv);
    switch (shape.type)
    {
    case SPHERE:
    {
        // NOTE: It may be faster to do these operations using Vec3 functions
        const Vec4 sphereToRay = vec4Sub(ray.origin, point(0, 0, 0));
        const double a = vec4Dot(ray.direction, ray.direction);
        const double b = 2 * vec4Dot(ray.direction, sphereToRay);
        const double c = vec4Dot(sphereToRay, sphereToRay) - 1;
        const double discriminant = (b * b) - (4 * a * c);
        Intersections sphereIntersections;
        if (discriminant < 0)
        {
            intersectionsCreate(&sphereIntersections, 0);
            return sphereIntersections;
        }
        double point1 = (-b - sqrt(discriminant)) / (2 * a);
        double point2 = (-b + sqrt(discriminant)) / (2 * a);
        intersectionsCreate(&sphereIntersections, 2);
        sphereIntersections.elem[0].shape = shape;
        sphereIntersections.elem[1].shape = shape;
        sphereIntersections.elem[0].t = point1;
        sphereIntersections.elem[1].t = point2;
        return sphereIntersections;
    }
    case PLANE:
    {
        Intersections planeIntersections;
        if (fabs(ray.direction.y) < MAT_EPSILON)
        {
            intersectionsCreate(&planeIntersections, 0);
        }
        else
        {
            intersectionsCreate(&planeIntersections, 1);
            planeIntersections.elem[0].shape = shape;
            planeIntersections.elem[0].t = -ray.origin.y / ray.direction.y;
        }
        return planeIntersections;
    }
    default:
        abort(); // TODO: Remove
    }
}

// Returns the "hit" (first non-negative) intersection.
// If a "hit" does exist, an intersection with a `NO_HIT` shape type is returned.
// Important: The intersection collection needs to be sorted.
Intersection hit(const Intersections intersections)
{
    for (size_t i = 0; i < intersections.size; i++)
    {
        if (intersections.elem[i].t >= 0)
        {
            return intersections.elem[i];
        }
    }
    return (Intersection){{NO_HIT, {{0}}, {{0}}, {0}}, -1};
}

// Returns the vector normal to the shape at point on the surfaces point.
// Important: The point must be on the shape's surface.
Vec4 normal(const Shape shape, Vec4 point)
{
    switch (shape.type)
    {
    case SPHERE:
    {
        point = mat4VecMul(shape.transformInv, point); // move outside of switch for other shapes
        point = vec4Sub(point, point(0, 0, 0));
        point = mat4VecMul(mat4Trans(shape.transformInv), point);
        point.w = 0;
        return vec4Norm(point);
    }
    case PLANE:
    {
        point = mat4VecMul(mat4Trans(shape.transformInv), vector(0, 1, 0));
        point.w = 0;
        return point;
    }
    default:
        abort();
    }
}

// Returns the value of light received by the camera on the point on a shape.
// Important: Ensure vectors are normalized.
Vec3 lighting(const Material material, const Light light, const Vec4 point, const Vec4 camera, const Vec4 normal, const bool inShadow)
{
    const Vec3 effectiveColor = vec3Prod(material.color, light.intensity);
    const Vec4 vecLight = vec4Norm(vec4Sub(light.position, point));
    const Vec3 ambient = vec3Mul(effectiveColor, material.ambient);
    Vec3 diffuse;
    Vec3 specular;
    const double lightDotNormal = vec4Dot(vecLight, normal);
    if (inShadow || signbit(lightDotNormal)) // NOTE: Test if < 0 is better for branch prediction
    {
        diffuse = color(0, 0, 0); // NOTE: Test if the use of compound literals affects performance
        specular = color(0, 0, 0);
    }
    else
    {
        diffuse = vec3Mul(effectiveColor, material.diffuse * lightDotNormal);
        const Vec4 vecReflect = vec4Reflect(vec4Neg(vecLight), normal);
        const double reflectDotCamera = vec4Dot(vecReflect, camera);
        if (reflectDotCamera <= 0)
        {
            specular = color(0, 0, 0);
        }
        else
        {
            specular = vec3Mul(light.intensity, material.specular * pow(reflectDotCamera, material.shininess));
        }
    }
    return vec3Add(vec3Add(ambient, diffuse), specular); // Potentially split into 2 return statements to avoid unnecessary additions
}

// World destructor
void worldDestroy(World *world)
{
    free(world->lights);
    free(world->shapes);
    world->lightCount = 0;
    world->shapeCount = 0;
    world->lights = NULL;
    world->shapes = NULL;
}

// Returns the default world
World defaultWorld(void)
{
    World world;
    world.lightCount = 1;
    world.lights = malloc(sizeof(Light));
    world.lights[0] = light(-10, 10, -10, 1, 1, 1);
    world.shapeCount = 2;
    world.shapes = malloc(sizeof(Shape) * 2);
    world.shapes[0] = sphere(IDENTITY, MATERIAL);
    world.shapes[0].material.color = color(0.8, 1, 0.6);
    world.shapes[0].material.diffuse = 0.7;
    world.shapes[0].material.specular = 0.2;
    world.shapes[1] = sphere(scaling(0.5, 0.5, 0.5), MATERIAL);
    if (world.lights == NULL || world.shapes == NULL)
    {
        abort();
    }
    return world;
}

// Calculates the intersections between the ray and the shapes in the world,
// returning them as a sorted intersection collection.
Intersections intersectWorld(World world, Ray ray)
{
    Intersections worldIntersections;
    intersectionsCreate(&worldIntersections, 0);
    for (size_t i = 0; i < world.shapeCount; i++)
    {
        Intersections shapeIntersections = intersect(world.shapes[i], ray);
        for (size_t j = 0; j < shapeIntersections.size; j++)
        {
            intersectionsPush(&worldIntersections, shapeIntersections.elem[j]);
        }
        intersectionsDestroy(&shapeIntersections);
    }
    if (worldIntersections.size > 0)
    {
        intersectionsSort(&worldIntersections);
    }
    return worldIntersections;
}

// Returns weather a certain point is shadowed by the light at the given index in the world
// Important: `lightIndex` begins at zero
bool isShadowed(const World world, const size_t lightIndex, const Vec4 point)
{
    Vec4 vec = vec4Sub(world.lights[lightIndex].position, point);
    Ray ray = {point, vec4Norm(vec)};
    Intersections lightIntersections = intersectWorld(world, ray);
    Intersection lightHit = hit(lightIntersections);
    intersectionsDestroy(&lightIntersections);
    if (lightHit.shape.type != NO_HIT && lightHit.t < vec4Mag(vec))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Pre-computes certain vectors and returns a Computations object
Computations prepareComputations(const Intersection intersection, const Ray ray)
{
    Computations computations;
    computations.shape = intersection.shape;
    computations.t = intersection.t;
    computations.point = rayPos(ray, intersection.t);
    computations.camera = vec4Neg(ray.direction);
    computations.normal = normal(intersection.shape, computations.point);
    if (vec4Dot(computations.normal, computations.camera) < 0)
    {
        computations.normal = vec4Neg(computations.normal);
        computations.inside = true;
    }
    else
    {
        computations.inside = false;
    }
    computations.overPoint = vec4Add(computations.point, vec4Mul(computations.normal, MAT_EPSILON));
    return computations;
}

// Calculates the color of a certain point
Vec3 shadeHit(const World world, const Computations computations)
{
    Vec3 hitColor = color(0, 0, 0);
    for (size_t i = 0; i < world.lightCount; i++)
    {
        hitColor = vec3Add(hitColor,
                           lighting(computations.shape.material, world.lights[i],
                                    computations.point,
                                    computations.camera,
                                    computations.normal, isShadowed(world, i, computations.overPoint)));
    }
    return hitColor;
}

// Returns the color that the ray receives in the world
Vec3 colorAt(const World world, const Ray ray)
{
    Intersections worldIntersections = intersectWorld(world, ray);
    const Intersection rayHit = hit(worldIntersections);
    intersectionsDestroy(&worldIntersections);
    if (rayHit.shape.type == NO_HIT)
    {
        return color(0, 0, 0);
    }
    else
    {
        Computations computations = prepareComputations(rayHit, ray);
        return shadeHit(world, computations);
    }
}

// Camera constructor
Camera cameraInit(const size_t hsize, const size_t vsize, const double fov, const Mat4 transform)
{
    Camera camera = {hsize, vsize, fov, .transform = transform,
                     .transformInv = mat4Inv(transform)};
    const double halfView = tan(camera.fov / 2);
    const double aspect = (double)hsize / vsize;
    if (aspect >= 1)
    {
        camera.halfWidth = halfView;
        camera.halfHeight = halfView / aspect;
    }
    else
    {
        camera.halfWidth = halfView * aspect;
        camera.halfHeight = halfView;
    }
    camera.pixelSize = (camera.halfWidth * 2) / hsize;
    return camera;
}

Canvas *render(const Camera camera, const World world)
{
    Canvas *image = canvasCreate(camera.hsize, camera.vsize);
    if (image == NULL) // Move canvas error handling code inside the canvas functions
    {
        abort();
    }
    for (size_t y = 0; y < camera.vsize; y++)
    {
        for (size_t x = 0; x < camera.hsize; x++)
        {
            const Ray ray = rayPixel(camera, x, y);
            const Vec3 color = colorAt(world, ray);
            canvasPixelWrite(image, x, y, color);
        }
    }
    return image;
}
