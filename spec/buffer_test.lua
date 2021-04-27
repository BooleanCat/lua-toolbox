local buffer = require('toolbox.buffer')
local bytes = require('toolbox.bytes')

local when = describe

describe('buffer', function()
  describe('new', function()
    it('creates a buffer', function()
      assert.is_not_nil(buffer.new())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #buffer.new())
    end)

    when('initialised with a toolbox.bytes', function()
      it('has initial length of the argument', function()
        assert.are.equal(3, #buffer.new(bytes.new('foo')))
      end)
    end)

    when('called with something other than a toolbox.bytes', function()
      it('returns an error', function()
        assert.has_error(
          function() buffer.new('foo') end,
          "bad argument #1 to 'new' (toolbox.bytes expected, got string)"
        )
      end)
    end)
  end)

  describe('bytes', function()
    it('returns a copy of the buffer contents', function()
      assert.are.equal(
        bytes.new('foo'),
        buffer.new(bytes.new('foo')):bytes()
      )
    end)
  end)
end)
