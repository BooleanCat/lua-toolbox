local buffer = require('toolbox.buffer')

local when = describe

describe('buffer', function()
  describe('new', function()
    assert.are_equal(
      'toolbox.buffer',
      debug.getmetatable(buffer.new()).__name
    )
  end)
end)
