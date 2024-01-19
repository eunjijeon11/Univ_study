# 팩토리 패턴
새로운 객체를 생성할 때마다 분기를 만들어 다른 구상 클래스로 인스턴스를 생성하면 유연성이 떨어진다.  
팩토리 패턴에서는 인스턴스를 만드는 부분을 캡슐화해서 분리한다.  
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/764ded13-832e-4ce6-99e6-983284cb66a7)

## 간단한 팩토리 패턴
인스턴스 생성 부분을 캡슐화한다.
```java
public class SimpleFactory {
  public pizza createPizza(String type) {
    Pizza pizza = null;
    if (type.equals("cheese")) {
      pizza = new CheesePizza();
    } else if (type.equals("clam")) {
      pizza = new ClamPizza();
    }
    return pizza;
  }
}
```
이렇게 생성 로직을 팩토리 클래스로 만들고
```java
public class PizzaStore {
  SimplePizzaFactory factory;

  public PizzaStore(SimplePizzaFactory factory) {
    this.factory = factory;
  }

  public Pizza orderPizza(String type) {
    Pizza pizza;
    pizza = factory.createPizza(type);
    pizza.prepare();
    return pizza;
  }
}
```
new operator를 함수로 대체한 것을 알 수 있다.  
하지만 이러한 방법은 단순히 생성 부분만 떼어 클래스로 만들었을 뿐이므로, 팩토리 패턴에서 제품군을 하나만 사용할 때만 사용할 수 있다.  
또 클래스로 이루어져있어 확장이 어렵다. (OCP 위배)

# 팩토리 메소드 패턴
만약 피자를 만드는 가게가 여러군데라면 어떨까? 팩토리별로 로직이 다르거나 생성되는 프로덕트 인스턴스가 다를 것이다.  
그런 상황에서는 스토어를 인터페이스(또는 추상 클래스)로 만들고 서브클래스에서 인스턴스 종류를 결정하는 메소드를 만들자.  

```java
public class PizzaStore {
  public Pizza orderPizza(String type) {
    Pizza pizza;
    pizza = createPizza(type);
    pizza.prepare();
    return pizza;
  }

  abstract Pizza createPizza(String type);
}
```
스토어에는 팩토리 메소드를 만들어두고, 서브클래스에서 이를 재정의하여 인스턴스 종류를 결정한다.
```java
public class NYPizzaStore extends PizzaStore {
  Pizza createPizza (String item) {
    if (item.equals("cheese")) {
      return new NYStyleCheesePizza();
    } else if (item.equals("Clam")) {
      return new NYStyleClamPizza();
    } else return null;
  }
}
```
이 때 PizzaStore의 orderPizza에서는 어떤 종류의 인스턴스가 생성되는지 모르기 때문에, 느슨한 결합이 성립한다.  
생성하는 프로덕트인 Pizza 클래스는 아래와 같다.
```java
public abstract class Pizza {
  String name;
  String dough;
  ArrayList toppings = new ArrayList();

  void prepare() {
    System.out.println("Preparing " + name);
  }
}

public NYStyleCheesePizza extends Pizza {
  public NYStyleCheesePizza() {
    name = "NY Style Sauce and Cheese Pizze";
  }
}

public ChicagoStyleCheesePizze extends Pizza {
  public ChicagoStyleCheesePizza() {
    name = "Chicago Style Cheese Pizze";
  }

  // also can override methods in Pizza class
}
```
결론적으로 팩토리 메소드 패턴은 다음과 같이 이뤄져 있다.  
**The Creator Classes**
- abstract creator class: PizzaStore
- concrete creator classes: NYPizzaStore, ChicagoPizzaStore...

**The Product Classes**
- abstract product class: Pizza
- concrete product classes: NYStyleCheesePizza, ChicagoStyleClamPizza...

![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/f936c339-0253-47be-a376-d6186a755973)


## 다른 시각 - 평행 클라스 위계
![image](https://github.com/eunjijeon11/Univ_study/assets/61264183/6f37c1ed-96fb-4123-ab80-3aefe1f0b420)

## 장단점
장점
- 수정에 닫혀있고 확장에 열려있는 OCP 원칙을 지킬 수 있다.
- 다른 객체 없이 상속을 통해 구현해서 메모리를 아낄 수 있다.

단점
- 많은 클래스를 정의해야해서 코드량이 증가한다.

# DIP (Dependency Inversion Principle)
추상화된 것에 의존하게 만들고, 구상 클래스에 의존하지 않게 만든다.  
즉, 다른 객체를 사용할 때 구상 클래스가 아니라 인터페이스나 추상 클래스 등의 추상화된 것을 사용해야 한다는 것.  
ex) PizzaStore는 추상 클래스인 Pizza에 의존하고 있다.

## DIP 지키기
- 변수에 구상 클래스의 레퍼런스를 저장하지 않는다.
- 구상 클래스에서 유도된 클래스를 만들지 않는다.
- 베이스 클래스에 이미 구현되어 있는 메소드를 오버라이드하지 않는다.
모두를 지킬 수는 없으므로 바뀔 확률이 큰 부분을 정의하고 그런 부분에서 규칙을 지키도록 노력해야한다.

## Inversion
보통의 객체지향에서 생각하는 것과 반대로 생각하기 때문에 Inversion이 붙었다.  
더 높은 레벨인 PizzaStore도 Pizza에 의존하고 있기 때문에 PizzaStore -> Pizza <- concrete product classes 같은 형태가 된다.  

# 추상 팩토리 클래스
<img width="748" alt="image" src="https://github.com/eunjijeon11/Univ_study/assets/61264183/710e8c7b-56b3-4527-b075-1aa47c30498b">
구상 클래스로 특정짓는 대신 관련된 프로덕트를 만들 수 있는 인터페이스를 제공하는 방법이다.
