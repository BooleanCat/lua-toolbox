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

  describe('__len', function()
    when('empty', function()
      it('has length 0', function()
        assert.are_equal(0, #data.new())
      end)
    end)

    when('instantiated with an integer', function()
      it('has length equal to the integer', function()
        assert.are_equal(6, #data.new(6))
      end)
    end)

    when('instantiated with a string', function()
      it('has the length of the string', function()
        assert.are_equal(7, #data.new('pikachu'))
      end)
    end)
  end)

  describe('__tostring', function()
    when('empty', function()
      it('presents as empty square braces', function()
        assert.are_equal(
          '[]',
          string.format('%s', data.new())
        )
      end)
    end)

    when('instantiated with an integer', function()
      it('presents as space space separated hexadecimal zeroes surrounded by square brackets', function()
        assert.are_equal(
          '[00 00 00 00 00 00]',
          string.format('%s', data.new(6))
        )
      end)
    end)

    when('instantiated with a string', function()
      it('presents as space space separated hexadecimal values surrounded by square brackets', function()
        assert.are_equal(
          '[70 69 6B 61 63 68 75]',
          string.format('%s', data.new('pikachu'))
        )
      end)
    end)
  end)

  describe('__eq', function()
    when('tested with two empty data values', function()
      it('considers them equal', function()
        assert.is_true(data.new() == data.new())
      end)
    end)

    when('tested with two values of different length', function()
      it('considers them not equal', function()
        assert.is_false(data.new() == data.new(1))
      end)
    end)

    when('tested with two values of equal length but different content', function()
      it('considers them not equal', function()
        assert.is_false(
          data.new('charmander') == data.new('bulbasaur')
        )
      end)
    end)

    when('tested with two values of equal length but different content', function()
      it('considers them not equal', function()
        assert.is_false(
          data.new('gengar') == data.new('mewtwo')
        )
      end)
    end)

    when('tested with two values of equal length and equal content', function()
      it('considers them not equal', function()
        assert.is_true(
          data.new('pikachu') == data.new('pikachu')
        )
      end)
    end)
  end)

  it('has function stubs', function()
    local bytes = data.new()

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
