project('Aktina', 'c', version: '0.1.0', license : 'BSD-3-Clause', 
  default_options : ['c_std=c18', 'warning_level=3'])

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)
criterion_dep = dependency('criterion', required : false)
if criterion_dep.found()
  tuples_test = executable('tuples_tests', ['src/tuples.c', 'test/tuples_test.c'], dependencies : [m_dep, criterion_dep])
  test('Tuple operations', tuples_test, protocol : 'tap',
    args : '--tap', env : ['LSAN_OPTIONS=suppresions=../LSAN_suppresions.txt,print_suppresions=0'])
endif
