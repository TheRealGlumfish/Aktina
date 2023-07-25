project('Aktina', 'c', version: '0.1.0', license : 'BSD-3-Clause',
  default_options : ['c_std=c18', 'warning_level=3'])

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)
criterion_dep = dependency('criterion', required : false)

if criterion_dep.found()
  tuples_test = executable('tuples_tests', ['src/tuples.c', 'test/tuples_test.c'], dependencies : [m_dep, criterion_dep])
  canvas_test = executable('canvas_tests', ['src/canvas.c', 'test/canvas_test.c', 'src/vectors.c'], dependencies : [m_dep, criterion_dep])
  matrices_test = executable('matrices_tests', ['src/matrices.c', 'test/matrices_test.c', 'src/tuples.c'], dependencies : [m_dep, criterion_dep])
  vectors_test = executable('vectors_tests', ['src/vectors.c', 'test/vectors_test.c'], dependencies : [m_dep, criterion_dep])
  test('Tuple operations', tuples_test,
    protocol : 'tap', args : ['--tap', '--always-succeed', '-j0'],
    env : ['LSAN_OPTIONS=suppressions=../LSAN-suppressions.txt,print_suppressions=0'])
  test('Canvas operations', canvas_test,
    protocol : 'tap', args : ['--tap', '--always-succeed', '-j0'],
    env : ['LSAN_OPTIONS=suppressions=../LSAN-suppressions.txt,print_suppressions=0'])
  test('Matrix operations', matrices_test,
    protocol : 'tap', args : ['--tap', '--always-succeed', '-j0'],
    env : ['LSAN_OPTIONS=suppressions=../LSAN-suppressions.txt,print_suppressions=0'])
  test('Vector, matrix and transformation operations', vectors_test,
    protocol : 'tap', args : ['--tap', '--always-succeed', '-j0'],
    env : ['LSAN_OPTIONS=suppressions=../LSAN-suppressions.txt,print_suppressions=0'])
endif
