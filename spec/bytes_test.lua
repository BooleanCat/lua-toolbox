local types = require('toolbox.types')
local bytes = require('toolbox.bytes')

local when = describe

describe('bytes', function()
  describe('new', function()
    it('creates a byte array', function()
      assert.is_not_nil(types.bytes())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #types.bytes())
    end)

    when('called with an integer', function()
      it('creates a byte array of that size', function()
        assert.are.equal(10, #types.bytes(10))
      end)

      it('writes 0s to the array', function()
        assert.are.equal(
          '[00 00 00 00 00]',
          string.format('%s', types.bytes(5))
        )
      end)
    end)

    when('initialised with a string', function()
      it('creates a byte array with the string length', function()
        assert.are.equal(5, #types.bytes('hello'))
      end)
    end)
  end)

  describe('__eq', function()
    it('considers bytes with matching size and content as equal', function()
      assert.are.equal(types.bytes('foo'), types.bytes('foo'))
    end)

    it('considers bytes with different sizes as not equal', function()
      assert.are_not.equal(types.bytes(), types.bytes(2));
    end)
  end)

  describe('__tostring', function()
    it('prints hex codes of bytes', function()
      assert.are.equal(
        '[68 65 6C 6C 6F]',
        string.format('%s', types.bytes('hello'))
      )
    end)

    it('prints a zero length byte array', function()
      assert.are.equal('[]', string.format('%s', types.bytes()))
    end)

    it('prints length one byte arrays', function()
      assert.are.equal('[68]', string.format('%s', types.bytes('h')))
    end)
  end)

  describe('concat', function()
    it('concatenates two byte arrays', function()
      local b = types.bytes('abc') .. types.bytes('de')
      assert.are.equal(
        '[61 62 63 64 65]',
        string.format('%s', b)
      )
    end)

    it('does not modify the originals', function()
      local a = types.bytes('a')
      local b = types.bytes('b')
      local _ = a .. b

      assert.are.equal('[61]', string.format('%s', a))
      assert.are.equal('[62]', string.format('%s', b))
    end)

    when('the first array is empty', function()
      it('concatenates the arrays', function()
        local b = types.bytes() .. types.bytes('de')
        assert.are.equal(
          '[64 65]',
          string.format('%s', b)
        )
      end)
    end)

    when('the second array is empty', function()
      it('concatenates the arrays', function()
        local b = types.bytes('abc') .. types.bytes()
        assert.are.equal(
          '[61 62 63]',
          string.format('%s', b)
        )
      end)
    end)

    when('both arrays are empty', function()
      it('concatenates the arrays', function()
        local b = types.bytes() .. types.bytes()
        assert.are.equal(#b, 0)
      end)
    end)
  end)
end)
