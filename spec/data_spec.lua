local data = require 'toolbox.data'

local when = describe

describe('data', function()
  describe('new', function()
    it('does not return nil', function()
      assert.is_not_nil(data.new())
    end)

    it('can be instantiated with a string', function()
      assert.is_not_nil(data.new('test'))
    end)

    it('can be instantiated with an integer', function()
      assert.is_not_nil(data.new(10))
    end)

    it('cannot be instantiated with an invalid type', function()
      assert.has_error(
        function() data.new({}) end,
        "bad argument #1 to 'new' (string or integer expected, got table)"
      )
    end)
  end)

  it('has function stubs', function()
    local bytes = data.new()

    assert.are.equal('function', type(bytes.__eq))
    assert.are.equal('function', type(bytes.__tostring))
    assert.are.equal('function', type(bytes.__len))
    assert.are.equal('function', type(bytes.__concat))
  end)
end)

-- A slice will be a reference to some part of data. The slice will contain a
-- weak reference to the original data, an offset and a size.
--
-- Datas will contain references to all of their slices. When a data in garbage
-- collected, it will mark all slices as dead. Future operations against dead
-- slices shall fail.
describe('slice', function()
  it('has function stubs', function()
    assert.are.equal('function', type(data.slice))
  end)
end)
