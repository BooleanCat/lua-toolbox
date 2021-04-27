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
    ['toolbox.types'] = {
      sources = {'src/lib/types.c'},
      incdirs = {'src/include'}
    },
    ['toolbox.bytes'] = {
      sources = {'src/lib/bytes.c'},
      incdirs = {'src/include'}
    }
  }
}
