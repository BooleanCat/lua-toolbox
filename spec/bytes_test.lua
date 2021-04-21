local bytes = require('toolbox.bytes')

describe("bytes", function()
  it("can be initialised", function()
    assert.is_not_nil(bytes.new())
  end)

  it("has initial length 0", function()
    assert.are.equal(0, #bytes.new())
  end)

  describe('when initialised with a number', function()
    it('creates a byte array of that size', function()
      assert.are.equal(10, #bytes.new(10))
    end)
  end)

  describe('when initialised with a string', function()
    it('creates a byte array with the string length', function()
      assert.are.equal(5, #bytes.new('hello'))
    end)
  end)

  it('supports __tostring', function()
    assert.are.equal('bytes(17)', string.format('%s', bytes.new(17)))
  end)

  it('supports __eq', function()
    assert.are.equal(bytes.new('foo'), bytes.new('foo'))
  end)
end)
