package = 'toolbox'

version = 'git-1'

source = {
  url = 'git://github.com/BooleanCat/lua-toolbox'
}

description = {
  summary = '',
  detailed = '',
  homepage = '',
  license = ''
}

dependencies = {
  'lua == 5.4',
}

build = {
  type = 'builtin',
  modules = {
    ['toolbox.bytes'] = {
      sources = {'src/lib/bytes.c'},
      incdirs = {'src/include'}
    },
    ['toolbox.buffer'] = {
      sources = {'src/lib/buffer.c'},
      incdirs = {'src/include'}
    },
    ['toolbox.data'] = {
      sources = {'src/lib/data.c'},
      incdirs = {'src/include'}
    }
  }
}
