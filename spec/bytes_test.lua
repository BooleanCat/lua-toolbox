local bytes = require('toolbox.bytes')

local when = describe

describe('bytes', function()
  describe('buffer', function()
    it('creates a bytes buffer', function()
      assert.is_not_nil(bytes.buffer())
    end)
  end)
end)
