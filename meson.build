project(
  'AOC25',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

dependencies = [
]

run = executable(
  'AOC25',
  'aoc25.c',
  dependencies : dependencies,
  install : true,
)

run_target('run',command: [run])
