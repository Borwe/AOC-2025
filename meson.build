project(
  'AOC25',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

bo_arena = dependency('bo_arena', required: true)

c_args = ['-std=c11', '-Wall', '-Werror', '-Wextra', '-pedantic']

dependencies = [
  bo_arena
]

d1p1 = executable(
  'd1p1',
  'day1_p1.c',
  c_args: c_args,
  dependencies: dependencies,
  install: true)
run_target('day1_p1', command: [d1p1, '../data/day1.txt'])
d1p2 = executable(
  'd1p2',
  'day1_p2.c',
  c_args: c_args,
  dependencies: dependencies,
  install: true)
run_target('day1_p2', command: [d1p2, '../data/day1.txt'])


d2p1 = executable(
  'd2p1',
  'day2_p1.c',
  c_args: c_args,
  dependencies: dependencies,
  install: true)
run_target('day2_p1', command: [d2p1, '../data/day2.txt'])
d2p2 = executable(
  'd2p2',
  'day2_p2.c',
  c_args: c_args,
  dependencies: dependencies,
  install: true)
run_target('day2_p2', command: [d2p2, '../data/day2.txt'])

run = executable(
  'AOC25',
  'aoc25.c',
  dependencies : dependencies,
  install : true,
)

run_target('run',command: [run])
