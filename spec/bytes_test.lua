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
  end)
end)
