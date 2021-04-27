local bytes = require('toolbox.bytes')
local types = require('toolbox.types')

local when = describe

describe('bytes', function()
  describe('buffer', function()
    it('creates a bytes buffer', function()
      assert.is_not_nil(bytes.buffer())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #bytes.buffer())
    end)

    when('initialised with a toolbox.types.bytes', function()
      it('has initial length of the argument', function()
        assert.are.equal(3, #bytes.buffer(types.bytes('foo')))
      end)
    end)

    when('called with something other than a toolbox.types.bytes', function()
      it('returns an error', function()
        assert.has_error(
          function() bytes.buffer('foo') end,
          "bad argument #1 to 'buffer' (toolbox.types.bytes expected, got string)"
        )
      end)
    end)
  end)
end)
