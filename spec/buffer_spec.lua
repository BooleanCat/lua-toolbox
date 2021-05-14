local buffer = require('toolbox.buffer')
local data = require('toolbox.data')

local when = describe

describe('buffer', function()
  describe('new', function()
    it('creates a toolbox.buffer', function()
      assert.are_equal(
        'toolbox.buffer',
        debug.getmetatable(buffer.new()).__name
      )
    end)

    when('initialised with a toolbox.data', function()
      it('buffers the data', function()
        local buf = buffer.new(data.new('squirtle'))

        assert.are_equal(
          'toolbox.buffer',
          debug.getmetatable(buf).__name
        )
        assert.are_equal(data.new('squirtle'), buf:data())
      end)
    end)

    when('initialised with an invalid type', function()
      it('returns an error', function()
        assert.has_error(
          function() buffer.new({}) end,
          "bad argument #1 to 'new' (toolbox.data expected, got table)"
        )
      end)
    end)
  end)

  describe('cap', function()
    it('returns 50 for a new buffer', function()
      assert.are_equal(50, buffer.new():cap())
    end)
  end)

  describe('__len', function()
    it('returns 0 for an empty buffer', function()
      assert.are_equal(0, #buffer.new())
    end)
  end)

  describe('__tostring', function()
    it('describes the length and capacity of the buffer', function()
      assert.are_equal(
        'toolbox.buffer<0, 50>',
        string.format('%s', buffer.new())
      )
    end)
  end)

  describe('__tbread', function()
    when('called with an invalid type', function()
      it('returns an error', function()
        assert.has_error(
          function() buffer.new():__tbread({}) end,
          "bad argument #1 to '__tbread' (toolbox.data expected, got table)"
        )
      end)
    end)
  end)

  describe('__tbwrite', function()
    it('writes data to the buffer', function()
      local buf = buffer.new()
      local size = buf:__tbwrite(data.new('pikachu'))

      assert.are_equal(7, size)
      assert.are_equal(data.new('pikachu'), buf:data())
    end)

    it('writes data sequentially', function()
      local buf = buffer.new()

      assert.are_equal(7, buf:__tbwrite(data.new('pikachu')))
      assert.are_equal(11, buf:__tbwrite(data.new(' charmander')))

      assert.are_equal(data.new('pikachu charmander'), buf:data())
    end)

    when('writing more data than the cap would accomodate', function()
      pending('grows', function()
        local buf = buffer.new()

        for i = 1, 10 do
          assert.are_equal(10, buf:__tbwrite(data.new('charmander')))
        end

        assert.are_equal(100, #buf:data())
      end)
    end)

    when('called with an invalid type', function()
      it('reurns an error', function()
        assert.has_error(
          function() buffer.new():__tbwrite({}) end,
          "bad argument #1 to '__tbwrite' (toolbox.data expected, got table)"
        )
      end)
    end)
  end)

  describe('data', function()
    it('returns empty data for an empty buffer', function()
      assert.are_equal(
        data.new(),
        buffer.new():data()
      )
    end)
  end)

  describe('reset', function()
    it('clears the buffer', function()
      local buf = buffer.new(data.new('charmander'))
      buf:reset()

      local destination = data.new(10)

      local n = buf:__tbread(destination)
      assert.are_equal(0, n)
    end)
  end)
end)
