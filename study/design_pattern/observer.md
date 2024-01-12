# Observer 패턴
옵저버 패턴은 Observer들이 관찰하고 있는 subject의 상태가 변할 때 각 Observer에게 이를 알리는 행동패턴이다.  
대상(subject)와 Observer 클래스 인스턴스로 구성된다.
- subject는 상태를 저장하고 제어한다.
- subject은 하나만 존재할 수 있다.
- Observer는 상태를 소유할 수 없다.
- Observer는 여러 개가 존재할 수 있다.
- 일대다 관계가 성립한다.
- 여러 객체가 동일한 데이터를 제어하는 것보다 더 깔끔한 객체지향 디자인을 만들 수 있다.
## 구조
1. Subject (interface)
- register, remove, notify에 대한 구조 정의
2. Observer (interface)
- update에 대한 구조 정의
3. ConcreteSubject
- Subject를 상속하는 클래스
- register, remove, notify 내용 정의
- getState, setState 함수 정의
- Observer 리스트를 갖고있음
4. ConcreteObserver
- Observer를 상속하는 클래스
- 생성 시 subject가 정해짐
- update 내용 정의: subject로부터 pull
- 해당 Observer만의 특정 기능 등등등

## loose coupling
객체들이 상호작용할 수 있지만 서로를 잘 모르는 관계이다.
- Observer 패턴이 이에 해당한다.
- subject과 Observer는 특정 인터페이스를 구현한다는 사실만 안다.
- 새로운 형식의 Observer를 추가해도 subject을 변경할 필요가 없다.
- subject와 Observer는 독립적으로 재사용할 수 있다.
- subject와 Observer가 달라져도 서로에게 영향을 미치지 않는다.

## Push vs Pull
- Push: subject에서 Observer로 데이터를 보냄
- Pull: observer에서 subject의 데이터를 당겨 옴
pull 방식이 더 바람직하다. 새로운 옵저버를 추가하기 쉬운, 확장이 용이한 디자인이기 때문이다.

## 기타
- 비슷한 패턴으로 출판-구독 패턴이 있는데 이는 비동기 api 처리와도 관련이 있다.
- 나중에 MVC 패턴에도 적용이 된다.

## Code
subject
```java
public interface Subject {
  void register(Observer o);
  void remove(Observer o);
  void notify();
}

public class WeatherData implements Sybject {
  private List<Observer> observers;
  private float _temperature;
  private float _humidity;
  private float _pressure;

  public WeatherData() {
    this.observers = new ArrayList<>();
  }

  @Override
  public void register(Observer o) {
    observers.add(o);
  }

  @Override
  public void remove(Observer o) {
    int index = observers.indexOf(o);
    if (index != -1) {
      observers.remove(o);
    }
  }

  @Override
  public void notify() {
    for (Observer o: observers) {
      o.update();
    }
  }

  public void mesurementsChanged() {
    notify();
  }

  public void setMesurements(float temperature, float humidity, float pressure) {
    this._temperature = temperature;
    this._humidity = humidity;
    this._pressure = pressure;
    mesurementsChanged();
  }

  public float getTemperature() {
    return _temperature;
  }

  public float getHumidity() {
    return _humidity;
  }

  public float getPressure() {
    return _pressure;
  }
}
```
observer
```java
public interface Observer {
  void update();
}

public class ConditionDisplay implements Observer, DisplayElement {
  private WeatherData weatherData;
  public ConditionDisplay(WeatherData weatherData) {
    this.weatherData = weatherData;
    weatherData.register(this);
  }

  @Override
  public void display(float temperature, float humidity, float pressure) {
    //...
  }

  @Override
  public void update() {
    int temperature = weatherData.getTemperature();
    int humidity = weatherData.getHumidity();
    int pressure = weatherData.getPressure();

    display(temperature, humidity, pressure);
  }
}
```
