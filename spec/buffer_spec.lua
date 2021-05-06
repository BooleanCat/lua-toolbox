local buffer = require('toolbox.buffer')

describe('buffer', function()
  describe('new', function()
    assert.are_equal(
      'toolbox.buffer',
      debug.getmetatable(buffer.new()).__name
    )
  end)

  it('has method stubs', function()
    local buf = buffer.new()

    assert.are_equal('function', type(buf.__len))
    assert.are_equal('function', type(buf.__tostring))
    assert.are_equal('function', type(buf.__tbread))
    assert.are_equal('function', type(buf.__tbwrite))
    assert.are_equal('function', type(buf.data))
    assert.are_equal('function', type(buf.reset))
    assert.are_equal('function', type(buf.cap))
  end)
end)
