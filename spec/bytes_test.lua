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
end)
