//local temp = 10
//
//function foo(a)
//print("foo", a)
//temp = temp + 5
//return coroutine.yield(2 * a)
//end
//
//co = coroutine.create(function(a, b)
//    print("co-body", a, b)
//    local r = foo(a + 1 + temp)
//    temp = temp + 10
//    print("co-body", r)
//    local r, s = coroutine.yield(a + b, a - b)
//    print("co-body", r, s)
//    return b + temp, "end"
//    end)
//
//print("main", coroutine.resume(co, 1, 10))
//print("main", coroutine.resume(co, "r"))
//print("main", coroutine.resume(co, "x", "y"))
//print("main", coroutine.resume(co, "x", "y"))
