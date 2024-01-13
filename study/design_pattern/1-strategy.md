# 도입
객체만 사용한다
- 객체에 정의된 속성을 사용하지 않거나 변경해야하는 인스턴스가 있을 때마다 속성(함수)을 재정의해야한다.

인터페이스를 사용한다
- 위같은 문제는 사라진다.
- 하지만 공통되는 속성을 변경하기 위해서 모든 객체의 코드를 변경해야한다.
- 코드를 복붙해야한다.

이러한 상황을 해결하기 위해 디자인패턴을 사용할 수 있다.

# 전략 패턴
## 디자인 원칙
> 📌 1. 애플리케이션에서 새로운 요구사항이 있을 때마다 달라지는 부분을 찾아내고, 달라지지 않는 부분과 분리한다.

달라지는 부분을 찾아 나머지 코드에 영향을 주지 않도록 캡슐화한다.  
나중에 바뀌지 않는 부분에는 영향을 미치지 않고 그 부분만 고치거나 확장할 수 있다.  

모든 패턴은 시스템의 일부분을 **다른 부분과 독립적으로 변화시킬 수 있는** 방법들을 제공한다.

> 📌 2. 구현보다는 인터페이스(상위 형식)에 맞춰서 프로그래밍한다.

객체가 코드에 고정되지 않도록 상위 형식(supertype)에 맞춰 프로그래밍한다.
=> 다형성(polymorphism)을 활용한다.
1. 변수를 선언할 때 추상 클래스나 인터페이스(Animal)같은 상위 형식으로 선언한다.
2. 객체를 변수에 대입할 때 상위 형식을 구제적으로 구현한 형식이라면 어떤 객체든 넣을 수 있기 때문이다.
3. 변수를 선언하는 클래스에서 실제 객체의 형식을 몰라도 된다.
```java
// implementation
Dog dog = new Dog();
dog.bark();

// interface / supertype
Animal animal = new Dog();
animal.makeSound(); // bark
Animal animal2 = new Cat();
animal2.makeSound(); // meow

// assign the concrete implementation at runtime
animal = getAnimal(); // We don't know the actual subtype
animal.makeSound();
```
- 반복해서 사용되지만 그 내용이 변하는 속성들에 대해 supertype으로 인터페이스를 만들어두고, 클래스로 실제 내용을 implement 해놓으면 재사용하기가 쉽다. 또한 새로운 속성이 추가되었을 때 상위 인터페이스는 변할 필요가 없다.

> 📌 3. 상속받기보단 합성(composition)을 이용한다 = 행동을 상속받는 대신 행동 객체를 부여받는다.

서브클래스를 만드는 방식으로 행동을 상속받으면 모든 서브클래스에서 행동을 상속받아야한다. => 유연성이 떨어진다.

구성으로 객체의 행동을 확장(부여받는 형식)하면 실행 중에 동적으로 행동을 설정할 수 있다.
- 새로운 코드를 만들어서 기능을 추가할 수 있다.
- 기존 코드를 건드리지 않고 수정할 수 있다.
- 코드 수정에 따른 버그나 부작용을 방지할 수 있다.

![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/11ec7bed-e100-4c4d-902a-ce1cf8077097)

생성자에서 행동을 부여하고, setter로 동적으로 행동을 설정할 수 있게 한다.

HAS-A: 부여받음
IS-A: 상속받음

## 전략 패턴
전략 패턴(정책 패턴): 특정한 계열의 알고리즘들을 정의하고, 각 알고리즘들을 캡슐화하여 이 알고리즘들을 해당 계열 안에서 상호 교체 가능하게 만든다.

변경 가능성이 큰 부분을 분리하고(concrete subclass) 인터페이스를 이용해 구현체로 캡슐화하여 동적으로 상호 교체할 수 있게 하는것이다.

3가지 원칙을 적용한 코드
```java
public interface FlyBehavior {
  public void fly();
}
```
```java
public class FlyNoWay implements FlyBehavior {
  @override
  public void fly() {
    // no fly
  }
}
```
```java
public abstract class Duck {
  FlyBehavior flyBehavior;

  public void performFly() {
    flyBehavior.fly();
  }

  public void setFlyBehavior(FlyBehavior fb) {
    this.flyBehavior = fb;
  }
}
```
```java
public class RubberDuck extends Duck {
  public RubberDuck() {
    this.flyBehavior = new FlyNoWay();
  }
}
```
- 오버헤드가 발생하지 않도록 해야한다. 이러한 패턴이 오히려 코드를 복잡하게 만들 수 있다.
- 추상화를 통한 이점을 충분히 파악하고 사용을 고려하자.
