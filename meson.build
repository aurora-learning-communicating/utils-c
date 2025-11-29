project('safety-utils-c', 'c')

fs = import('fs')

includes = []
modules = ['array', 'error', 'fileio', 'optional', 'pointer', 'result', 'syscall', 'logs']
intermediates = []

foreach module: modules
    if fs.exists(module)
        includes += include_directories(module)
    endif
    # module_object = static_library(module, )
endforeach

foreach module: modules
    source_file = module + '/' + module + '.c'
    if fs.exists(source_file)
        intermediates += static_library(module, module + '/' + module + '.c', include_directories: includes, install: false)
    endif
endforeach


test_dir = 'tests'
test_files = ['test_line.c', 'test_result.c', 'test_pointer.c', 'test_array.c']

foreach test_file: test_files
   test_name = test_file.split('.')[0]
   test_executable = executable(test_name, test_dir + '/' + test_file, include_directories: includes, link_with: intermediates)
   test(test_name, test_executable)
endforeach
