-- print(type(true))
-- a = 0;

-- if a then
--     print("a is true")
-- else
--     print("a is false")
-- end

-- print(type(print))

-- function func1(a,b,c)
--     return a,b,c,"eee",true;
-- end

-- print (func1("abc",123,false));

--函数当右值
    --匿名函数，函数本身没有名字，但被保存到了变量 sum1
    --Lua 中函数也是一种值，
    --所以可以赋值给变量、放进表、作为参数传给其他函数。
    -- local sum1 = function(a,b)
    --     return a+b;
    -- end
    -- print(sum1(1,2));
--函数当参数
    -- local function func3(functionname,a,b)
    --     return functionname(a,b);
    -- end
    -- print(func3(sum1,1,2));

--表
-- info= {
--     id = 123,
--     name = "lam",
--     sex = false
-- } 
-- info2 = {123,"lam",false}  --下标从1开始
--遍历表
-- for k,v in pairs(info) do
--     print(k,"=====",v);
-- end
--增删改查
-- info.age = 20;
-- info["country"] = "china";

-- info.sex = nil;
-- info["sex"] = nil;
--表嵌套
    -- info= {
    --     id = 123,
    --     name = "Lam",
    --     sex = false
    -- } 

    -- info2 = {456,"Dan",true} 

    -- info3 = {
    --     id = 789,
    --     name = "Tom",
    --     sex = true,
    --     777, "Zhang",true,
    --     info2,
    --     info4 = { id = 111,name = "Jerry",sex = false}

    -- }
    -- for k,v in pairs(info3) do
    --     print(k,"=====",v );
    --     if type(v) =="table" then
    --         for K2,V2 in pairs(v)do
    --             print("\t",K2,"=====",V2 );            
    --         end      
    --     end
    -- end

--逻辑运算符
--a,b = 1,2;
    -- print(a and b); --返回b的值

    -- a = false;
    -- print(a and b); --返回a的值

    -- print(a or b); --返回a的值
    -- a = false;
    -- print(a or b); --返回b的值
    --b = false;
    -- print(a or b); --返回a的值

--自写三目运算
    -- A,B,C = 1,2,3;
    --E = (A and {B} or {C})[1];
    --print(E);