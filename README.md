# hyNet
## callback.h
回调函数包装类，用于保存绑定和调用某个事件结束后的回调函数
## tcp_session.h
shared_from_this()用于解决shared_ptr与this的冲突，比如直接shared_ptr<T>(this)，就会构造出一个独立的智能指针，不用调用到引用计数