local buffer = require('toolbox.buffer')
local data = require('toolbox.data')

local when = describe

describe('buffer', function()
  describe('new', function()
    it('creates a buffer', function()
      assert.is_not_nil(buffer.new())
    end)

    it('has initial length 0', function()
      assert.are.equal(0, #buffer.new())
    end)

    when('initialised with a toolbox.data', function()
      it('has initial length of the argument', function()
        assert.are.equal(3, #buffer.new(data.new('foo')))
      end)
    end)

    when('called with something other than a toolbox.data', function()
      it('returns an error', function()
        assert.has_error(
          function() buffer.new('foo') end,
          "bad argument #1 to 'new' (toolbox.data expected, got string)"
        )
      end)
    end)
  end)

  describe('data', function()
    it('returns a copy of the buffer contents', function()
      assert.are.equal(
        data.new('foo'),
        buffer.new(data.new('foo')):data()
      )
    end)
  end)

  describe('__tostring', function()
    it('represents the buffer size', function()
      assert.are.equal(
        'toolbox.buffer[5]',
        string.format('%s', buffer.new(data.new('hello')))
      )
    end)
  end)

  describe('__tbread', function()
    it('reads data into a toolbox.data', function()
      local buf = buffer.new(data.new('hello'))
      local d = data.new(5)

      local n, done = buf:__tbread(d)

      assert.are.equal(5, n)
      assert.is_true(done)
      assert.are.equal(data.new('hello'), d)
    end)

    when('the destination is smaller', function()
      it('reads as much as possible into the destination', function()
        local buf = buffer.new(data.new('hello'))
        local d = data.new(3)

        local n, done = buf:__tbread(d)

        assert.are.equal(3, n)
        assert.is_nil(done)
        assert.are.equal(data.new('hel'), d)
      end)
    end)

    when('the destination is larger', function()
      it('reads the entire buffer', function()
        local buf = buffer.new(data.new('hello'))
        local d = data.new(7)

        local n, done = buf:__tbread(d)

        assert.are.equal(5, n)
        assert.is_true(done)
        assert.are.equal(
          '[68 65 6C 6C 6F 00 00]',
          string.format('%s', d)
        )
      end)
    end)

    when('a read has already occurred', function()
      it('continues reading from where it last finished', function()
        local buf = buffer.new(data.new('hello'))
        local d = data.new(3)

        local n, done = buf:__tbread(d)
        assert.are.equal(3, n)
        assert.is_nil(done)
        assert.are.equal(data.new('hel'), d)

        n, done = buf:__tbread(d)
        assert.are.equal(2, n)
        assert.is_true(done)
        assert.are.equal(data.new('lol'), d)

        n, done = buf:__tbread(d)
        assert.are.equal(0, n)
        assert.is_true(done)
        assert.are.equal(data.new('lol'), d)
      end)
    end)

    when('passing the wrong type of argument', function()
      it('raises an error', function()
        local buf = buffer.new(data.new('hello'))

        assert.has_error(
          function() buf:__tbread({}) end,
          "bad argument #1 to '__tbread' (toolbox.data expected, got table)"
        )
      end)
    end)
  end)

  describe('__tbwrite', function()
    it('reads data from a toolbox.data into the buffer', function()
      local d = data.new('hello')
      local buf = buffer.new()

      local n, err = buf:__tbwrite(d)
      assert.are.equal(5, n)
      assert.is_nil(err)
      assert.are.equal(data.new('hello'), buf:data())
    end)

    when('called multiple time', function()
      it('reads data from a toolbox.data into the buffer', function()
        local d = data.new('hello')
        local buf = buffer.new()

        local n, err = buf:__tbwrite(d)
        assert.are.equal(5, n)
        assert.is_nil(err)
        assert.are.equal(data.new('hello'), buf:data())

        n, err = buf:__tbwrite(d)
        assert.are.equal(5, n)
        assert.is_nil(err)
        assert.are.equal(data.new('hellohello'), buf:data())
      end)
    end)

    when('writing more than the capacity', function()
      it('grows', function()
        local d = data.new('hello')
        local buf = buffer.new()

        for _ = 1, 20 do
          local n, err = buf:__tbwrite(d)
          assert.are.equal(5, n)
          assert.is_nil(err)
        end

        assert.are.equal(100, #buf:data())
      end)
    end)
  end)

  describe('reset', function()
    it('empties the buffer', function()
      local buf = buffer.new(data.new('hello'))
      assert.are.equal(data.new('hello'), buf:data())

      buf:reset()

      assert.are.equal(0, #buf:data())
    end)
  end)
end)
