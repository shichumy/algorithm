/*
*实现线程安全的单例模式
*所谓非线程安全的单例模式是在多线程下存在创建多个实例的隐患
*/

//饿汉模式：提前构建单例模式的实例，这样就不会存在多线程下多个线程创建多个实例的情况
class Singleton{
    private:
        static const Singleton * m_instance;
        Singleton(){}
    pulic:
        static const Singleton * getInstance(){
            return m_instance;
        }
}

//在类的外部进行初始化
const Singleton* Singleton::m_instance = new Singleton();


//另外一种方式，懒汉模式
class Singleton{
    private:
        static Singleton * m_instance;
        Singleton(){}
    public:
        static Singleton* getInstance();
}
//每次通过getInstance()方法进行该类实例的获取时，都要加锁，加锁开销很大
Singleton* Singleton::getInstance(){
    lock();
    if(m_instance == NULL){
        m_instance = new Singleton();   
    }
    unlock();
    return m_instance;
}

//通过先判断该实例是否存在减少加锁的开销
Singleton* Singleton::getInstance(){
    if(m_instance == NULL){
        lock();
        if(m_instance == NULL){
            m_instance = new Singleton();
        }
        unlock();
    }
    return m_instance;
}

//通过定义局部静态变量的方式实现懒汉模式
class Singleton{
    private:
        Singleton(){}
    public:
        static Singleton& getInstance(){
            static Singleton instance;
            //C++0x之后提供了线程安全保证，不需要用lock()、unlock操作
            //lock();
            //static Singleton instance;
            //unlock();
            
            return instance;
        }
    
}
