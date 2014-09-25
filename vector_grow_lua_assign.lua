#!/usr/bin/env luajit

local socket = require("socket")

function main(arg)
   local n = tonumber(arg[1])
   local m = {}
   local v = {}
   local index = 1
   local t

   t = socket.gettime()
   m[0] = 0
   for i = 0, n - 1, n / 100 do
      for j = 0, (n / 100) - 1 do
         v[index] = j
         index = index + 1
      end
      m[i / (n / 100) + 1] = socket.gettime() - t
   end

   print("\"size\",\"time\"\n")
   for i = 0, 100 do
      io.write(string.format("%d,%f\n",  i * (n / 100), m[i]))
   end
end

main(arg)
