-- local a = true
-- local b = 0
-- local c = ""
-- local d = false
-- local e = nil
-- if a then
-- 	print("a")
-- else
-- 	print("not a")
-- 	end
-- if b then
-- 	print("b")
-- else
-- 	print("not b")
-- 	end
-- if c then
-- 	print("c")
-- else
-- 	print("not c")
-- 	end
-- if d then
-- 	print("d")
-- else
-- 	print("not d")
-- 	end
-- if e then
-- 	print("e")
-- else
-- 	print("not e")
-- end

-- local order = 3.99
-- local score = 98.01
-- print(math.floor(order)) -->output:3
-- print(math.ceil(score)) -->output:99


-- print "i love \"nzhsoft\""
-- print 'i love "nzhsoft"'
-- print 'nzhosft is \'great\''
-- print "nzhosft is 'great'"

-- local str3 = [["add\name",'hello']]
-- print(str3)
-- local str4 = [=[string have a [[]].]=]
-- print(str4)


-- str =
-- " \
-- <html> \
-- <head> \
-- <title> </title> \
-- </head>\
-- <body> \
-- <p>http://edu.nzhosft.cn</p> \
-- </body> \
-- </html> \
-- "
-- str =
-- [[
-- <html>
-- <head>
-- <title> </title>
-- </head>
-- <body>
-- <p>http://edu.nzhosft.cn</p>
-- </body>
-- </html>
-- ]]
-- print(str);

local corp = {
web = "www.edu.nzhsoft.cn", -- k = "web"
							-- v = "edu.nzsoft.cn"
telephone = "17090078295", -- k = "telephone"
							-- v = "17090078295"
staff = {"jack","Scott","Gary"},
10086, -- key = 1 v = 10086
10010, -- key = 2 v = 10010
[10] = 160, -- key = 10 v = 160
["city"] = "guangzhou"
}

-- print (corp.web)
-- print(corp.telephone)
-- print(corp["web"])
-- print(corp[1])
-- print(corp[10])
-- print(corp.staff[1])
-- print(corp["staff"])
-- print(corp.staff)
-- print(corp["staff"][2])
-- corp.staff[2] = "abc"
-- print(corp["staff"][2])

-- for i,v in ipairs(corp) do
-- 	print(i,v)
-- end
print("------------------")
-- for k,v in pairs(corp) do
-- 	if(type(k) == "table") then
-- 	-- if(k == corp.staff) then
-- 		print("k == corp.staff")
-- 		for t,v in pairs(k) do
-- 			print(t,v)
-- 		end
-- 	end
-- 	print(k,v)
-- end

-- print(type(corp))
-- print(type(corp) == type(table))


-- var = 99
-- local var = 98
-- function func()
-- var = 100

-- 	local var = 100
-- 	var = var + 1
-- 	print(var)
-- end

-- func()
-- print(var)
--[=[
x = 10 -- 全局变量
do -- 新的语句块
	local x = x -- 新的一个 'x', 它的值现在是 10
	print(x) --> 10
	x = x + 1  --11
	do -- 另一个语句块
		local x = x + 1 -- 又一个 'x'
		print(x) --> 12
	end
	print(x) --> 11
end
print(x)
]=]

-- a,b = 1,2,3,4
-- print(a,b)
-- c,d,e,f = 1,2,3
-- print(c,d,e,f)

-- local num = 1357
-- print(num % 2) -->打印 1
-- print((num % 2) == 1) -->打印 true. 判断 num 是否为奇数
-- print((num % 5) == 0) -->打印 false.判断 num 是否能被 5 整数


-- print(6/3) --2.0
-- print(10/3) --3.3333333333333
-- print(10/3.0) --3.3333333333333
-- print(10%3) --1
-- print(10%3.1) --0.7

-- local a = { x = 1, y = 0}
-- local b = { x = 1, y = 0}
-- if a == b then
-- print("a==b")
-- else
-- print("a~=b")
-- end
-- local c = a
-- if a == c then
-- print("a==c")
-- else
-- print("a~=c")
-- end
--output:
--a~=b
--a==c

-- local c = nil
-- local d = 0
-- local e = 100
-- print(c and d) -->打印 nil
-- print(c and e) -->打印 nil
-- print(d and e) -->打印 100
-- print(c or d) -->打印 0
-- print(c or e) -->打印 100
-- print(not c) -->打印 true
-- print(not d) -->打印 false


-- function my_print()
-- var = 100
-- end
-- my_print() --执行与不执行有差距吗？
-- print(var)

-- {
	-- print("aaaaaaa")
-- }

-- for i=10,1,-1 do
-- 	print(i)
-- end

-- for i=1,math.huge do
-- 	if(0.3*i^3 - 20*i^2 - 500 >= 0)then
-- 		print(i)
-- 		break;
-- 	end
-- end

-- goto ok
-- goto notok
-- do
-- 	local i = 1
-- 	print(i)
-- 	::notok::
-- 	i = i+ 1
-- 	::ok::
-- end

-- function func()
-- goto ok
-- local i = 1
-- print(i)
-- i = i+ 1
-- end
-- func()
-- ::ok::
-- print("goto out") -- no visible label 'ok' for <goto>

-- do

-- 	-- goto ok
-- 	goto notok
-- 	local i = 1
-- 	print(i)
-- 	::notok:: -- 本地变量的作用域内， 所以无法跳转
-- 	i = i + 1
-- 	::ok:: -- 本地变量的作用域结束， 所以可以跳转.
-- end 

-- do
-- 	print("hello lua")
-- 	local  x = io.read()
-- end

-- print([==[ [nzh\nsoft]]==]);
-- print "i love \"nzhsoft\""

-- print 'i love "nzhsoft"'
-- print 'nzhosft is \'great\''
-- print "nzhosft is 'great'"

-- str = "nzhosft"
-- print(str[4])

-- print(10 + '11')
-- print(type(10+'11'))

-- print("11" + 10)
-- print(type("11"+10))

-- print(10 .. "11")
-- print(type(10 .. "11"))


-- print(tonumber("11") + 10)
-- print(tostring(10) .. "111")

tab = {
	web = "www.baidu.com",
	["abc"] = 1110,
}
-- function func( ... )
-- 	-- body
-- end
-- print(type(tab) == "table")
-- print(type(10) == "number")
-- print(type(true) == "boolean")
-- print(type("10") == "string")
-- print(type(func) == "function")
-- print(type(nil) == "nil")

-- str = "abcDEFG"
-- strupper = string.upper(str)
-- strlower = string.lower(str)
-- print(str)
-- print(strupper)
-- print(strlower)
-- len = string.len(str);
-- len = #str
-- print(len)
-- print(#strlower)

-- str = "aabbbccccdef"
-- str1 = string.rep(str,1);
-- print(str1);
-- str = string.char(65,66,67,68,90,97,122,48,49,56,57,58,69,60);
-- print(str)

-- str = "123abc456,abc";
-- str1 = string.gsub(str,"abc","HHH");
-- str1 = string.reverse(str)
-- print(str1)

-- t = {"ax","Cy","mk","Bjlk"}
-- for i,v in ipairs(t) do
-- 	print(i,v)
-- end
-- table.sort(t, function ( a,b )
-- 	return string.lower(a) < string.lower(b);
-- end )

-- for k,v in pairs(t) do
-- 	print(k,v)
-- end
-- print(table.concat( t, "-"))
-- print(table.concat( t, "-",1,2))
-- print(table.concat( t, "-",2,4))

--[[
s4 = "Lua"
s5 = "nzhsoft"
print(string.format("Basic formatting %s==%s",s4,s5))

date = 2; month = 1; year = 2014
print(string.format("Date formatting %02d/%02d/%03d", date, month, year))

print(string.format("%.4f",1/3))
print(string.format("%c", 83) ) --输出 S
print(string.format("%+d", 17.0) ) --输出+17
print(string.format("%05d", 17)) --输出 00017
print(string.format("%o", 17) ) --输出 21

print(string.format("%x", 13) ) --输出 d
print(string.format("%X", 13) ) --输出 D
print(string.format("%e", 1000) ) --输出 1.000000e+03
print(string.format("%E", 1000) ) --输出 1.000000E+03
print(string.format("%6.3f", 13) ) --输出 13.000

print(string.format("%s", "monkey") ) --输出 monkey
print(string.format("%10s", "monkey") ) --输出 monkey
]]

-- print(string.char())
-- print(type(string.char(48,49)))

-- print(string.byte("12345"))
-- print(string.byte("12345",3))
-- print(string.byte("12345",1,5))

s2 = "Lua nzsoft"
-- print(string.sub(s2,2))
-- print(string.sub(s2,2,100))
-- print(string.sub(s2,2,#s2))
-- print(#s2)
-- print(string.sub(s2,2,-2))
-- print(string.sub(s2,2,-1))
-- print(string.sub(s2,2,0))

-- ns = string.gsub(s2,"Lua","Language")
-- ns = string.gsub(s2,"abc","Language")
-- print(ns)

-- s3 = "Lua Tutorial"
-- print(string.find(s2,"nzsoft"))
-- print(string.find(s2,"nzsoft",-2))
-- tab = {
-- print("abc".."111"),
-- print("abc"..11),
-- print(11 .. "abc"),
-- print(10 .. 11),
-- }

-- array = {"Lua", "nzhsoft"}
-- print(#array)
-- for i= 0, 2 do
-- print(array[i])
-- end

array = {}
-- for i=1,3 do
-- 	array[i] = {}
-- 	for j=1,3 do
-- 		array[i][j] = i*j;
-- 	end
-- end

-- for i=1,3 do
-- 	for j=1,3 do
-- 		io.write(array[i][j]," ");
-- 	end
-- 	io.write("\n");
-- end

-- for k,v in pairs(array) do
-- 	print(k,v)
-- end

rows=3
columns=3

-- for i=1,3 do
-- 	for j = 1,3 do
-- 		array[(i-1)*columns + j] = i+j
-- 	end
-- end
-- for i=1,3 do
-- 	for j=1,3 do
-- 		io.write(array[(i-1) *columns + j]," ")
-- 	end
-- 	io.write("\n")
-- end

-- for i,v in ipairs(array) do
-- 	print(i,v)
-- end

-- for k,v in pairs(table) do
-- 	print(k,v)
-- end

-- print(#{1,2,3,4,5,6})

-- t = {11,22,33,nil,44,55,66,nil}
-- print(t[#t]) -- 输出最后一个元素
-- t[#t] = nil
-- print(#t)
-- t[#t + 1] = 999
-- print(#t)

-- t = {x = 1,y = 2, z = 3}
-- print(#t)

-- fruits = {"banana","orange","apple"}
-- 返回表中字符串连接后的结果
-- print("Concatenated string ",table.concat(fruits))

-- table.insert(fruits,"mango")
-- print(table.concat( fruits, "-"))

-- table.insert(fruits,2,"grapes")
-- print(table.concat( fruits, "-"))
-- print(fruits[#fruits])

-- -- table.remove(fruits,1)
-- table.remove(fruits)
-- print(table.concat( fruits, "-"))
-- print(#fruits)

-- t = {}
-- table.insert(t,1,"a")
-- table.insert(t,1,"b")
-- table.insert(t,1,"c")
-- table.insert(t,1,"d")

-- for i=1,#t do
-- 	print(#t)
-- 	print(table.remove(t,1))
-- end

-- fruits = {"banana","orange","apple"}

-- table.sort(fruits)
-- table.sort(fruits,function ( sa,sb )
	-- return sa >sb
-- end)
-- print(table.concat(fruits,"-"))

--[[
t = {"a","b","c"}
-- table.move(t,1,#t,2)
table.move(t,1,#t,4)

t[1] = "m"
for i=1,#t do
	-- print(t[i])
	io.write(t[i]," ")
end
print("")
print("-------------------")
table.move(t,2,#t,1)
print(#t)
for i=1,#t do
	-- print(i)
	io.write(t[i]," ")
end
print()
print("-------------------")
t[#t] = nil
print(#t)
for i=1,#t do
	-- print(i)
	io.write(t[i]," ")
end
print()
print("-------------------")
cp = table.move(t,1,#t,1,{})
print(#cp)
for i=1,#cp do
	-- print(i)
	io.write(t[i]," ")
end
print()
print("-------------------")
]]
-- t = {"a","b","c"}
-- t2 = {"x","y","z"}
-- cat = table.move(t,1,#t,#t2,t2)
-- for k,v in ipairs(cat) do --ipairs(t2)
-- 	print(k,v)
-- end

-- a = {[1] = 1,[999] = 999}
-- print(#a) --1
-- t = {[2] = 1,[999] = 999} --0
-- print(#t)

-- a2 = {[1] = 1,[2] = 999} --2
-- print(#a2)
-- a2 = {[1.1] = 1,[2] = 999}
-- print(#a2)
-- t2 = {1,999} --2
-- print(#t2)

-- array2 = {1,2,3,4,nil,6,7,8,9,10}
-- print("len =",#array2)
-- for k,v in ipairs(array2) do
-- print(k,v)
-- end
-- print("----------------------")
-- for i=1,#array2 do
-- 	-- io.write(array2[i]," ")
-- 	print(i,array2[i])
-- end
-- print("----------------------")
-- for k,v in pairs(array2) do
-- 	print(k,v)
-- end

t = {11,22,33,nil,44,55,nil}
-- tn = 7
-- for i=1,tn do
-- -- if t[i] then
-- -- print(t[i])
-- -- end
-- print(t[i])
-- end

-- for k,v in pairs(t) do
-- 	print(k,v)
-- end

-- array2 = {1,2,3,4,nil,6,7,8,9,10}
-- for k,v in pairs(array2) do
-- 	print(k,v)
-- end

-- a = {}
-- k = "x"
-- a[k] = 10
-- print(a[k])

-- a[20] = 'great'

-- print(a[k],a[20])
-- a["x"] = a["x"] + 1
-- print(a[k],a[20])
-- print("----------------")
-- print(a.x)
-- print(a.k)

-- i = 10; j = "10"; k = "+10"; -- k = "x10"
-- a = {}
-- a[i] = "number key"
-- a[j] = "string key"
-- a[k] = "another string key"
-- print (a[i]) --> number key
-- print (a[j]) --> string key
-- print (a[k]) --> another string key

-- print(a[tonumber(j)])
-- print(a[tonumber(k)])

-- for k,v in pairs(a) do
-- 	print(k,v)
-- end

-- a = {}
-- a[2.0] = 10 -->float key
-- a[2.1] = 20
-- print(a[2.0])
-- print(a[2.1])

-- for k,v in pairs(a) do
-- 	print(k,v)
-- end


-- stu = {
-- name = "guilin",
-- sex = "male",
-- age = 18,
-- org = "edu.nzhsoft.cn"
-- }
-- print(#stu)

-- for i,v in ipairs(stu) do
-- 	print(i,v)
-- end


-- a = {}
-- a["x"] = 10
-- b = a;

-- print(b["x"])
-- b["x"] = 20
-- print(a["x"])
-- a = nil
-- print(b["x"])
-- b= nil
-- print(b["x"])

t = {x = 1,y = 2, z = 3}
-- print(#t)
-- cp = table.move(t,1,#t,1,{})
-- for k,v in pairs(cp) do
-- print(k,v)
-- end

-- function copy( a,b )
-- 	a = a or{}
-- 	for k,v in pairs(b) do
-- 		a[k] = b[k];
-- 	end
-- 	return a
-- end

-- cp = copy(cp,t);

-- for k,v in pairs(cp) do
-- 	print(k,v)
-- end

-- a = {1,2,3}
-- b = {1,2,3}
-- if a == b then
-- print("a == b")
-- else
-- print("a != b")
-- print(a,b)
-- end

-- r = a
-- if r == a then
-- print("r == a")
-- print(r,a)
-- else
-- print("r != a")
-- end

-- a = {x = 1,y = 999}
-- array2 = {1,2,3,4,nil,6,7,8,9,10}
-- -- print(#a)
-- -- print(#array2)
-- for i,v in ipairs(array2) do
-- 	print(i,v)
-- end

-- a = true b = nil c = 300
-- print(a and b or c)
-- print((a and {b} or {c})[1])


-- local test = function(a,b,c,d,e,f,g)
-- 	a = a or 0
-- b = b or 0
-- c = c or 0
-- d = d or 0
-- e = e or 0
-- f = f or 0
-- g = g or 0
-- print(a,b,c,d,e,f,g)
-- end
-- test(1,2,3,4,5,6,7,8,9,10)
-- test(1,2,3,4)

a = 10
-- print(a + nil)
-- print(a > nil)
-- print( true or nil )
-- print( true and nil )
-- print( not nil )

local max = function (a,b)
if a > b then
return a
else
return b
end
end

-- local  m = max(1,nil)
-- print(m)

-- print "hello lua" --print ("hello lua")
-- print [[hello lua]] --print ([[hello lua]])
-- print {a = 1,b = 2} --print ({a = 1,b = 2})
-- type{} --type({})

-- s,e = string.find("nzhsoft lua education","lua")
-- print(s,e) -- 9 11

-- function maxinum( t )
-- 	idx = 1;
-- 	max = t[idx];
-- 	for i=2,#t do
-- 		if(t[i] > max) then
-- 			max = t[i];
-- 			idx = i
-- 		end
-- 	end
-- 	return max,idx;
-- end

-- max,index = maxinum({1,2,3,10,5,6})
-- print(max,index)


-- local func = function ( n )
-- if n >100 then return 111,999 end
-- end
-- local a,b = func(101)
-- print(a,b) --111 999
-- local a,b = func(99)
-- print(a,b) --nil nil

function f123() return 1, 2, 3 end
function f456() return 4, 5, 6 end
-- print(f123()) -- prints 1, 2, 3
-- print(f456()) -- prints 4, 5, 6
-- print((f123())) -- prints 1
-- print((f456())) -- prints 4
-- print(f123(), f456()) -- prints 1, 4, 5, 6
-- print(f456(), f123()) -- prints 4, 1, 2, 3
-- x,y,z = f123()
-- print(x,y,z)

-- x,y,z = f123(),99,999
-- x,y,z,a =999,99,f456()
-- print(x,y,z,a)
-- print(x,y,z)

-- t = {f456()}
-- for k,v in pairs(t) do
-- print(k,v)
-- end

-- t2 = {f456(),f123()}
-- t2 = {f456(),f123(),99}
-- for k,v in pairs(t2) do
-- 	print(k,v)
-- end

-- function abc( a,b,c )
-- 	print(a,b,c)
-- end
-- -- abc(f456())
-- abc(f123(),f456())

function func( ... )
	-- return f123()
	-- return f123(),f456()
	-- return (f123())
	-- return f123()+f456()
end

-- print(func())

-- function foo()
-- print(1)
-- return math.pi
-- print(2)
-- end
-- foo()

-- myprint = function(param)
-- print("This is my print function - ##", param, "##")
-- end
-- function add(num1, num2, functionPrint) --打印函数作为入参用于显示
-- result = num1 + num2
-- functionPrint(result)
-- end
-- myprint(10)
-- add(2, 5, myprint)

t = {
add = function (x, y) --表内
return x + y;
end
}
-- for k,v in pairs(t) do
-- 	print(k,v)
-- end
-- print(t["add"](1,2))
-- print(t.add(1,2))

t.minus = function ( a,b )
	return a - b;
end

-- print(t.minus(6,3))
function t.plus( a,b )
	return a *b;
end
-- print(t.plus(3,4))

function func( ... )
	print(#{...})
	local a,b,c = ...;
	a = a or 0;
	b = b or 0;
	c = c or 0;

	print(a,b,c)
end
-- func(1,2,3,4,5,6)
-- func(1,2)



function add( ... )
	local sum = 0;
	-- local arg = {...}
	local arg = table.pack(...)
	print(arg.n)
	-- for i=1,#arg do
	for i=1,arg.n do
		if(arg[i] ~= nil) then 
			sum = sum + arg[i];
		end
	end
	-- for i,v in ipairs(arg) do
	-- 	sum = sum + v;
	-- end
	return sum
end

-- print(add(1,2,3,4,5,6))
-- print(add(1,2,nil,3,4,5,6,nil))


-- print(select(1,"a","b","c"))
-- print(select(3,"a","b","c"))
-- print(select("#","a","b","c"))
-- print(select("#","a",nil,"b","c"))
-- print(select(1,"a",nil,"b","c"))

function add( ... )
	for i = 1,select("#",...)do
		print(select(i,...));
	end
end

-- add(1,2,3,4,5,nil,6)
function func(  )
	return 1,2,3,4,5,6
end
-- print(1+func())
-- print(1+select(3,4,5,6))

function average( ... )
	local sum = 0
	local len = select("#",...)
	local nilcount = 0;
	for i=1,len do
		if(select(i,...)) then 
			sum = sum + select(i,...)
		else
			nilcount = nilcount + 1;
		end
	end
	avg = sum / (len-nilcount);
	return avg
end

-- print(average(1,2,3,4,nil,5,nil,6,7,nil))

function write( fmt,... )
	return io.write(string.format(fmt,...))
end
-- print(write("%d %s %f",10,"abc",11.11))
-- print(table.unpack({10,20,30}))
-- a,b = table.unpack({10,20,30})
-- print(a,b)


-- b,d = string.find("hello","ll")
-- print(b,d)
-- print(string.find("hello","ll"))
f = string.find
t = {"hello","ll"}
-- print(f(table.unpack(t)))
-- print(table.unpack({"Sun", "Mon", "Tue", "Wed"}, 2, 4)) --范围


network = {
{name = "server1",ip = "192.168.1.101"},
{name = "server3",ip = "192.168.1.103"},
{name = "server2",ip = "192.168.1.102"},
{name = "server4",ip = "192.168.1.104"}
}
comp = function ( a,b )
	return a.name > b.name
end
-- table.sort(network,function ( a,b )
-- 	return a.name < b.name
-- end)
table.sort(network,comp)

-- for i,v in ipairs(network) do
-- 	for name,ip in pairs(v) do
-- 		print(name,ip)
-- 	end
-- end

-- function func()
-- local function foo()
-- print("返回函数内部定义的函数")
-- end
-- return foo
-- end
function func()
return function ()
print("返回函数内部定义的函数1")
end
end
f = func();
-- f()

-- function func(n)
-- 	local function foo()
-- 		print("n:",n)
-- 		n = n+1;
-- 	end 
-- 	return foo
-- end

-- f = func(2000)
-- f()
-- f()
-- f()
function func(n)
	local function foo1()
		print(n)
	end
	local function foo2()
		n = n + 10
	end
	return foo1,foo2
end

-- f1,f2 = func(10)
-- f1()
-- f2()
-- f1()
-- f1()
-- f2()
-- f1()

-- f3 = func(200)
-- f3()
-- f2()
-- f3()
-- t = {10}
-- table.getn(t)

t = {1,2,3,nil,4,5,6,nil}
-- print(table.unpack(t))
-- t1 = table.pack(table.unpack(t))
-- t1 = table.pack(1,2,3,nil,4,5,6,nil)
-- print(t1.n)

-- function getsum(  )
-- 	local n = 0
-- 	 -- return function ( i )
-- 	function foo( i )
-- 		n = n+i
-- 		return n
-- 	end
-- 	return foo
-- end
-- local sum = getsum()
-- for i=1,11 do
-- 	print(string.format("0+...+%d = %d",i,sum(i)))
-- end

function func()
	local a=0 
	local b = 1
	-- local a,b =0,1 
	function foo()
		b,a = a+b,b
		return a
	end
	return foo
end

-- f = func()
-- for i=1,10 do
-- 	print(f())
-- end

array = {10,20,30,40,50,60,70}

-- function func()
-- 	local i = 0
-- 	return function (tab)
-- 		i = i + 1;
-- 		return tab[i];
-- 	end
-- end
-- function func(tab)
-- 	local i = 0
-- 	return function ()
-- 		i = i + 1;
-- 		return tab[i];
-- 	end
-- end

-- iter = func(array)

-- while true do
-- 	-- element = iter(array)
-- 	element = iter();
-- 	if element == nil then
-- 		break;
-- 	else
-- 		io.write(element," ")
-- 	end
-- end

tab = {"lua","nz"}
function traverse(tab)
	local i = 0
	local count = #tab
	return function ()
		i = i + 1
		if(i <= count) then
			-- return i,tab[i]
			return tab[i]

		end
	end
end

-- for k,v in traverse(tab) do
-- 	print(k,v)
-- end
-- for v in traverse(tab) do
-- 	print(v)
-- end

-- for _,v in pairs(tab) do
-- 	print(v)
-- end

-- local function fact( n )
-- 	if(n == 1) then 
-- 		return 1
-- 	else
-- 		return n* fact(n-1)
-- 	end
-- end
-- local fact
-- fact = function ( n )
-- 	if(n == 1) then 
-- 		return 1
-- 	else
-- 		return n* fact(n-1)
-- 	end
-- end

-- print(fact(5))
function foo(n)
if n > 0 then return foo(n-1) end
end
-- print(foo(10000))

s = "hello world"
i,j = string.find(s,"hello")
-- print(i,j)
-- print(string.sub(s,i,j))

-- i,j = string.find(s,"l")
-- print(i,j)
-- i,j = string.find(s,"llll")
-- print(i,j)

-- -- i,j = string.find("a[word]","[")
-- i,j = string.find("a[word]","[",1,true)
-- print(i,j)

s = [[
abc
efgg
xyz
]]
local t = {}
-- print(string.find(s,"\n",1))
-- print(#s)

-- local i = 0
-- while true do
-- 	i = string.find(s,"\n",i+1)
-- 	if i == nil then
-- 		break
-- 	end
-- 	t[#t+1] = i
-- end

-- for i,v in ipairs(t) do
-- 	print(i,v)
-- end

-- print(string.match("hello world","worw"))
-- date = "Today is 17/7/1990"
-- d = string.match(date,"%d+/%d+/%d+")
-- print(d)

-- s,c = string.gsub("hello world","wor","abc")
-- print(s,c)
-- print(string.gsub("hello world","l","abc"))

s,e = string.gsub("nzhosft is great","abc","xyz")
-- print(s,e)

-- print(string.gsub("all lii","l","x",2))

local str = "12china34,is,56great"
local itr_func = string.gmatch(str,"%d+")
-- print("itr_func is",itr_func)
-- print("itr_func ret is ",itr_func())
-- print("itr_func ret is ",itr_func())
-- print("itr_func ret is ",itr_func())
-- print("itr_func ret is ",itr_func())

-- t = {}
-- for v in string.gmatch(str,"%d+") do
-- 	print(v)
-- 	t[#t+1] = v
-- end
-- for k,v in pairs(t) do
-- 	print(k,v)
-- end

-- s = "hello world from Lua"
-- for w in string.gmatch(s,"%a+") do
-- 	print(w)
-- end
local attrstr = "nb=nzshoft, nb=nzshoft, name=lua"

-- print(string.gmatch(attrstr,"%w+=%w+")())
-- itr = string.gmatch(attrstr,"%w+=%w+")
itr = string.gmatch(attrstr,"(%w+)=(%w+)")
-- print(itr())
-- print(itr())
-- print(itr())
-- print(itr())
-- t = {}
-- for k,v in string.gmatch(attrstr,"(%w+)=(%w+)") do
-- 	print(k,v)
-- 	t[k] = v
-- end
-- for k,v in pairs(t) do
-- 	print(k,v)
-- end

-- print(string.gsub("hello,up-down","%a","."))
-- print((string.gsub("hello,up-down","%a",".")))
-- print(string.gsub("hello,up-down","%A","."))

text = [[
ab1cd2efg3xyz5
---AEIOUaeiou---
]]

-- print(string.gsub(text,"[135]","_"))
-- print(string.gsub(text,"[AEIOUaeiou]"," "))

text = [[
one, and two; and three
1,22,333,555,abcd
]]

-- print(string.gsub(text,"%a+","nz"))
-- for v in string.gmatch(text,"%d+") do
-- 	print(v)
-- end

text = [[
()
( )
( )
]]

-- print(string.gsub(text,"%(%s*%)","{}"))
c = "int x; /*x*/ int y; /*y*/"
-- print(string.gsub(c,"/%*.*%*/","-"))
-- print(string.gsub(c,"/%*.+%*/","&"))
-- print(string.gsub(c,"/%*.-%*/","^"))
-- print(string.gsub(c,"/%*.?%*/","$"))

-- digit = [[
-- 123xxxx+456xxx-111
-- ]]

-- print(string.gsub(digit,"[+-]%d*","&"))
-- print(string.gsub(digit,"[+-]%d*","&"))

-- for v in string.gmatch(digit,"[+-]%d+") do
-- 	print(v)
-- end

s = "a (enclosed (in) parentheses ) line"
-- print(string.gsub(s,"%b()",""))
-- print(string.gsub(s,"%b{}","&"))
pair = "org = nzhosft abc = xyz"

-- for k,v in string.gmatch(pair,"(%a+)%s*=%s*(%a+)") do
-- 	print(k,v)
-- end

-- date = "Today is 17/7/1990"
-- for y,m,d in string.gmatch(date,"(%d+)/(%d+)/(%d+)") do
-- 	print(y,m,d)
-- end


s = [[then he said: "It's all "right"]]

-- for v in string.gmatch(s,"[\"].*[\"]") do
-- 	print(v)
-- end
-- q,qc = string.match(s,"([\"'])(.-)%1")
   -- q,qc = string.match(s,"([\"'])(.-)%1")
-- print(q,qc) --" It's all righ

s = "a = [=[[[ something ]] ]==] ]=]; print(a)"
-- print(s)
-- p = "%[(=*)%[(.*)%]%1%]"
   p = "%[(=*)%[.*%]%1%]"

-- x,y = string.match(s,p)
-- print(x,y)
-- print(string.match(s,p))
-- print(string.gmatch(s,p)())

-- x = string.gsub("hello world", "(%w+)", "%1 %1")
-- print(string.match("hello world", "(%w+)"))
-- print(string.match("hello world", "%w+"))
-- print(x)
-- x = string.gsub("hello world", "(%w+)", "%0 %0")
-- print(x)
-- x = string.gsub("hello world", "(%w+)", "%0 %0",1)
-- print(x)

-- print(string.gsub("hello world", "(%w+)", "%1 %1"))
-- print(string.gsub("hello world", "%w+", "%0 %0"))
-- print(string.gsub("hello world", "(%w+)", "%1 %1"))
-- print(string.gsub("hello world", "%w+", "%0 %0",1))
 
 -- print(string.gsub("hello world from lua","(%w+)%s+(%w+)","%2 %1"))

-- print(string.gsub("\t a bc d ","^%s*(.-)%s*$","%1"))
-- print(string.gsub("\t a bc d ","^%s*(.*)%s*$","%1"))
-- print(string.match("/t a bc d ","^$"))
-- print(#"\t a bc d ")
-- print(#"a bc d")

-- local t = {name="lua",version="5.3"}
-- print(string.gsub("$name-$version.tar.gz","%$(%w+)",t))

-- x = string.gsub("4+5 = $return 4+5$","%$(.*)%$",function (s)
-- 	return load(s)()
-- end)
-- print(x)

-- print(string.gsub("4+5 = $return 4+5$","%$(.*)%$",function (s)
-- 	return load(s)()
-- end))

-- print(load("return 3 + 5")())

-- print(string.gsub("PATH=$PATH,os=$OS","%$(%w+)",os.getenv))
-- x = string.gsub("PATH = $PATH,os = $OS","%$(%w+)",os.getenv)
-- print(x)

-- x = string.gsub("PATH = $PATH, os = $OS", "%$(%w+)", os.getenv)
-- print(x) 

-- print(string.match("abcd123efg456","(%d+)%a*(%d+)"))
-- print(string.match("abcd123efg456","/d"))
-- print(string.match("abcd123efg456","^%d{3}$"))

-- local a = {1,2,3}
-- local b = {4,5,6}
-- local c = a + b;
-- for i,v in pairs(c) do
-- 	print(i,v)
-- end

-- mytable = {}
-- mymetatable = {}
-- setmetatable(mytable,mymetatable)

t1 = {}
t2 = {}
-- print("t1:",t1)
-- print("t2:",t2)
-- print("set:",setmetatable(t1,t2))
-- print("get:",getmetatable(t1))
-- print("set:",setmetatable({},{}))

local a = {1,2,3}
local b = {4,5,6}

mt = {}
function mt.__add(a,b)
	local n = #a
	local ret = {}
	for i=1,n do
		ret[i] = a[i] + b[i]
	end
	return ret
end

setmetatable(a,mt)
setmetatable(b,mt)
c = a+b 
-- for k,v in pairs(c) do
-- 	print(k,v)
-- end

c = {x = 1, y = 2, z = 3}
d = {x = 1, y = 2, z = 3}

-- if c == d then
-- 	print("c==d")
-- else
-- 	print("c~=d")

-- end
meq = {}
function meq.__eq(a,b)
	if c.x == d.x and c.y == d.y and c.z == d.z then
		return true
	else
		return false
	end
end

setmetatable(c,meq)
setmetatable(d,meq)

-- if c == d then
-- 	print("c==d")
-- else
-- 	print("c~=d")

-- end

other = {foo = 3}
-- t = {}
-- setmetatable(t,{__index=other})
t = setmetatable({},{__index=other})

-- print(t.foo)
-- print(t.bar)

-- prototype = {x = 0, y = 0, width = 100, height = 100}
-- mt = {__index = prototype}
-- function new( o )
-- 	w = setmetatable(o,mt)
-- 	return w
-- end

-- t = new({x=11})
-- t = new{x=11}

-- print(t.x)
-- print(t.y)
-- print(t.width)

-- mytable = {}
-- mt = {__index = function ( t,k )
-- 	print(t,k)
-- 	return true
-- end}

-- setmetatable(mytable,mt)
-- print(mytable)
-- print(mytable.key)

-- mytable = { key1 = "raw value" }
-- mt = {}
-- mt.__index = function ( t,k )
-- 	if k == "key2" then
-- 		return "meta value"
-- 	else
-- 		return nil
-- 	end
-- end
-- setmetatable(mytable,mt)
-- mytable = setmetatable({key1 = "raw value"},{
-- 	__index = function ( t,k )
-- 		if k == "key2" then
-- 			return "xxxmeta value"
-- 		else
-- 			return nil
-- 		end
-- 	end
-- })

-- print(mytable.key1,mytable.key2)

-- prototype = {x = 0, y = 0, width = 100, height = 100}

-- mt = {__index = function ( t,k )
-- 	return prototype[k]
-- end}
-- function new( o )
-- 	w = setmetatable(o,mt)
-- 	return w
-- end

-- t = new({y = 123},mt)

-- print(t.x)
-- print(t.y)
-- print(t.width)
-- print(t.z)

-- mytable = {key = 999}
-- print(mytable.key)
-- -- mytable.newkey = 111
-- -- print(mytable.newkey)

-- t = {}
-- mt = {__newindex = t,__index = t}

-- setmetatable(mytable,mt)
-- mytable.newkey = 11

-- print(mytable.newkey)
-- print(t.newkey)
-- mytable.key = 100
-- mytable.newkey = 900
-- print(mytable.newkey)
-- print(t.newkey)
-- print(t.key)
-- print(mytable.newkey)

-- mnt = {
-- 	__newindex = function (t,k,v)
-- 		print(t,k,v)
-- 	end
-- }

-- mb= {key = 100}

-- setmetatable(mb,mnt)
-- print(mb)
-- mb.newkey = 999
-- print(mb)


-- mt = {__newindex = function (t,k,v)
-- print(t,k,v)
-- end}
-- mytable = {key = 111}
-- setmetatable(mytable,mt)
-- print(mytable)
-- mytable.newkey = 999

-- t = {}
-- mt = {__newindex = function (_,k,v)
-- 	t[k] = v
-- end,__index = t}

-- mytable = {a = 11}
-- setmetatable(mytable,mt)
-- print(mytable)
-- mytable.b = 200;
-- print(mytable.a)
-- print(mytable.b)
-- print(t.b)

-- mytable = {x=0}
-- setmetatable(mytable,{__index = {y = 1}})
-- print(mytable.x)
-- print(mytable.y)
-- print(rawget(mytable,"x"))
-- print(rawget(mytable,"y"))

-- t = {}
-- mytable = {x =0}
-- setmetatable(mytable,{__newindex =t})
-- mytable.y = 999
-- print(t.y)

-- rawset(mytable,"z",99)
-- print(t.x)
-- print(t.z)
-- print(mytable.z)

pow = {}
setmetatable(pow,{__call = function ( t,x )
	return x*x;
end})

-- print(pow(3))
t = {}
setmetatable(t,{__call = function (t,a,b,c)
	return (a+b)*c
end})

-- print(t(4,5,6))
-- print(t.a)
-- print(t.b)
-- print(t.c)

mytable = setmetatable({10,2,2},{__tostring = function (t)
	sum = 0;
	for k,v in pairs(t) do
		-- print(k,v)
		sum = sum + v
	end
	return "和:" .. sum
end})

-- print(mytable)

t = {
	abc = 123
}

-- array = {1,2,3,4,5}
array = {1,2,3,nil,4,5}

function traverse()
	local i = 0
	local function iterator(array)
		i = i + 1
		return array[i]
	end
	return iterator
end

itr = traverse()

-- while true do
-- 	x = itr(array)
-- 	if x ~= nil then
-- 		print(x)
-- 	end
-- end

t = {10,20,30,40,50,60}
-- function mypairs(table)
-- 	local idx = 0
-- 	local count = #table
-- 	return function ()
-- 		idx = idx+1
-- 		if idx < count then
-- 			-- return idx, table[idx]
-- 			return table[idx]

-- 		end		
-- 	end
-- end

-- for v in mypairs(t) do
-- 	print(v)
-- end

-- do
-- local _f,_s,_v = pairs(t)
-- while true do
-- 	local k,v = _f(_s,_v)
-- 	if k == nil then break end
-- 	_v = k
-- ----------------------------------
-- 	print(k,v)
-- ----------------------------------
-- end
-- end

function square(mx,idx)
	if idx < mx then
		idx = idx +1
		return idx,idx*idx
	end
end

-- do 
-- local _f,_s,_v = square,3,0

-- while true do
-- 	local k,v = _f(_s,_v)
-- 	if k == nil then
-- 		break;
-- 	end
-- 	_v = k
-- 	print(k,v)
-- end

-- end

-- for k,v in square,4,0 do
-- 	print(k,v)
-- end

function squares(mx)
	return square,mx,0
end
-- for k,v in squares(5) do
-- 	print(k,v)
-- end


t = {10,20,30,nil,40,50,60,70}

-- function mypairss(table,idx)
-- 	idx = idx + 1
-- 	if table[idx] ~= nil then
-- 		return idx,table[idx]
-- 	end
-- end
function mypairss(table,idx)
	local myt = table.pack(table.unpack(table))
	print("myt.n:",myt.n)
	idx = idx + 1
	if idx < myt.n then

		if table[idx] ~= nil then
			return idx,table[idx]
		end
	end
end

function _mypairss(table)
	-- return mypairss,table,0
	return mypairss,table,0
	
end
-- do 
-- local _f,_s,_v = mypairss,t,0
-- while true do 
-- 	local k,v = mypairss(_s,_v)
-- 	if k == nil then
-- 		break
-- 	end
-- 	_v = k
-- 	print(k,v)	
-- end
-- end

-- for k,v in _mypairss(t) do
-- 	print(k,v)
-- end
print("-------------------")
for k,v in pairs(t) do
	print(k,v)
end