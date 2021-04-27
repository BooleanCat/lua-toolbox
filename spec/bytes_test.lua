local bytes = require('toolbox.bytes')

local when = describe

describe('bytes', function()
  describe('buffer', function()
    it('creates a bytes buffer', function()
      assert.is_not_nil(bytes.buffer())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #bytes.buffer())
    end)

    when('called with something other than a byte slice', function()
      it('returns an error', function()
        assert.has_error(
          function() bytes.buffer('foo') end,
          "bad argument #1 to 'buffer' (toolbox.types.bytes expected, got string)"
        )
      end)
    end)
  end)
end)
