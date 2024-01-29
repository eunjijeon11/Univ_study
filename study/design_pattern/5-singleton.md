# 싱글톤 패턴
클래스 인스턴스를 하나만 만들고, 그 인스턴스로의 전역 접근을 제공하는 것  
- private 생성자
- getInstance() 로 인스턴스 반환

## 고전적 방법
```java
public class Singleton {
  private static Singleton uniqueInstance;

  private Singleton() {} // private 생성자

  public static Singleton getInstance() { // getInstance()
    if (uniqueInstance == null) {
      uniqueInstance = new Singleton();
    }
    return uniqueInstance;
  }
}
```
문제점: 멀티스레드일때 여러 개의 인스턴스가 생성될 수 있다.

## 해결 방법
1. getInstance 동기화
함수에 동시에 한개의 스레드만이 접근할 수 있도록 만든다. 다만 성능이 100배정도 나빠진다.
```java
public static syncronized Singleton getInstance() {
  //
}
```

2. 인스턴스를 처음부터 만들기
```java
public class Singleton {
  private static Singleton uniqueInstance = new Singleton();
}
```
메모리 낭비가 일어날 수 있다.

3. DCL (Double Checked Locking) 사용하기
DCL은 syncronized로 멀티스레드 환경에서 Lazy initializing을 시킬때 발생할 수 있는 data race(생성자 호출 단계에서 JVM의 특성 때문에 아직 존재하지 않는 인스턴스에 접근하게 되어 프로그램 오류가 발생하는 경우)를 막기 위한 방법.
```java
public class Singleton {
	private volatile static Singleton uniqueInstance;
 
	private Singleton() {}
 
	public static Singleton getInstance() {
		if (uniqueInstance == null) {
			synchronized (Singleton.class) {
				if (uniqueInstance == null) {
					uniqueInstance = new Singleton();
				}
			}
		}
		return uniqueInstance;
	}
}
```
위 방법들은 클래스 로더가 2개 이상일 때, 리플랙션, 직렬화, 역직렬화가 사용됐을 때 문제시될 수 있다.

## 해결법
1. Enum 사용
```java
public enum EnumSingleton {
    uniqueInstance;
}
```
리플랙션 공격에 안전하고, 직렬화가 보장된다.  
Eager initialization 문제와 Enum을 상속하지 않을 때 문제가 발생한다.
초기화 시 의존성 주입이 문제될 수 있다.

2. Lazy Holder
```java
public class Singleton {

    private Singleton() {}
    
    // private static inner class 인 LazyHolder
    private static class LazyHolder {
        // LazyHolder 클래스 초기화 과정에서 JVM 이 Thread-Safe 하게 instance 를 생성
        private static final Singleton instance = new Singleton();
    }

    // LazyHolder 의 instance 에 접근하여 반환
    public static Singleton getInstance() {
        return LazyHolder.instance;
    }
    
}
```
private static class인 lazyholder 안에 final로 인스턴스를 선언하고 있다.  
final이므로 변수가 다시 생성되는 것을 막을 수 있다.  

- JVM 자체의 특성을 최대한 이끌어내어 성능 저하를 막는 방식이다.
- syncronized를 사용하지 않아도 JVM이 원자성을 보장한다.
- 역직렬화 수행시 개로운 객체가 생성되고, 리플랙션을 이용해 내부 생성자 호출이 가능하다.

LazyHolder는 최근 가장 많이 사용되는 기법이다.  
직렬화 등의 안정성이 중요시 되는 환경이라면 Enum, 성능이 중요시 되는 환경이라면 LazyHolder를 사용하도록 하자.

## 보충설명
- final: 수정이 불가능한 변수
- static: 객체 생성 없이도 사용 가능한, 객체의 공용 데이터
- Enum: 상수의 집합 (class의 필드가 모두 static 일 때와 같음)
- 직렬화: 데이터를 바이트 스트림으로 변환하여 다른 컴퓨터의 자바 시스템에서도 사용할 수 있게 함.
