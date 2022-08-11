arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11}
head = nil
local i = 1
while true do
	if arr[i] then
		head = {value = arr[i],next = head}
		i = i+1
	else
		break;
	end
end

-- while head do
-- 	print(head.value,head.next)
-- 	head = head.next
-- end

function iterator_withoutstatus(head,next)
	if next == nil then
		return head
	else
		return next.next
	end
end

function myipairs_withoutstatus(head)
	return iterator_withoutstatus,head,nil
end

-- do
-- 	local _f,_s,_v = myipairs_withoutstatus(head)
-- 	while true do
-- 		local v = _f(_s,_v);
-- 		if v == nil then
-- 			break;
-- 		end
-- 		_v = v;
-- 		print(v.value)
-- 	end
-- end

-- for v in myipairs_withoutstatus(head) do
-- 	print(v.value)
-- end
--==============================


function iterator_withstatus(head)
	local next = head
	return function ()
		head = next
		if head then
			next = head.next
			return head
		end
	end
end

-- do
-- 	local _f,_s,_v = iterator_withstatus(head)
-- 	while true do
-- 		local v = _f(_s,_v);
-- 		if v == nil then
-- 			break;
-- 		end
-- 		_v = v;
-- 		print(v.value)
-- 	end
-- end
for v in iterator_withstatus(head) do
	print(v.value)
end