#include <iostream>
#include <string>

/*
다이아몬드 상속 문제(Diamond Inheritance / Diamond Polymorphism)
하나의 조부모 Class -> 두개의 부모 Class -> 하나의 자식 Class 로 상속이 이어지는 경우,
여러가지 문제가 발생할 수 있다.
    1) 자식 Class 에서 부모 Class 의 멤버 충돌 발생
    2) 조부모 Class, 부모 Class 생성자 오류
    3) 기타 등등..
실제로는 여러 예상하지 못한 문제가 발생 가능해서 쓰지 않는 것을 추천한다고 하는데,
다이아몬드 상속 문제가 컴파일 되도록 구현하여 C++ 상속에 대해 학습해보자.
*/

class Person {
private:
    std::string name;            // private 변수는 외부 접근 불가. 상속에서도 마찬가지이다.
public:
    Person(std::string name){    // Constructor(생성자) : Class 명과 동일한, 반환값이 없는 함수.
                                 // 해당 Class 의 Instance 가 생성될 때 자동으로 실행되며, 보통 멤버 변수 초기화에 사용된다.
        this->name = name;       // this 포인터는 python 의 self 와 같은 느낌으로, 해당 클래스를 나타낸다.
        std::cout << "Person Instance is created."   << std::endl;
                                 // 생성자에 Person Instance 가 생성되었다는 문장 출력하여, 상속 시 생성자 우선순위 확인한다.
    }
    ~Person(){                   // Destructor(소멸자) : 프로그램이 끝나는 등 해당 Class 의 Instance 가 파괴(메모리 해제)될때 실행되는 함수.
        std::cout << "Person Instance is destroyed." << std::endl;
    }

    std::string getName(){       // Person 의 name 멤버 변수가 private 멤버 변수이기 때문에 외부에서 접근 불가하다.
        return name;             // Person Class 내에 name 변수를 반환하는 getName() public 멤버 함수를 넣는다.
    }                            // 이를 캡슐화 (encapsulation) 이라 한다. 자세한 내용은 객체지향(OOP)에 대해 공부해보자.
    void showName(){
        std::cout << "Name : " << getName() << std::endl;
    }
};

class Student : virtual public Person {  // class 선언 시 colon(:) 사용하여 상속받을 부모 class 를 지정해줄 수 있다.
private:                                 // 접근 지정자 앞에 virtual 을 붙여 가상 상속을 받아 뒤에 손자 class 생성 시 충돌을 피한다.  
    int studentID;                       // 상속받을때 접근 지정자는 default로 public 이다. 
                                         // private > protected > public 순으로 접근 지정자 우선순위가 있으며,
public:                                  // 상속 시 부모 class 의 멤버들의 접근 지정자 속성을 바꿀 수 있다.
    Student(int studentID, std::string name) : Person(name){
        this->studentID = studentID;     // 자식 class 의 생성자에서 부모 class 의 생성자를 호출하여 초기화 할 수 있다.
        std::cout << "Student Instance is created."     << std::endl;
    }
    ~Student(){
        std::cout << "Student Instance is destroyed."   << std::endl;

    }
    void show(){
        std::cout << "Student ID   : " << studentID   << std::endl;
        std::cout << "Student Name : " << getName() << std::endl;
    }
    void showName(){            // 부모 class 인 Person class에도 showName() 멤버 함수가 있으나, 자식 class 에서 함수 오버로딩을 해줬다.
        std::cout << "Student Name : " << getName() << std::endl;
    }
};

class Athlete : virtual public Person {
private:
    std::string sportType;
public:
    Athlete(std::string sportType, std::string name) : Person(name){
        this->sportType = sportType;
        std::cout << "Athlete Instance is created."     << std::endl;
    }
    ~Athlete(){
        std::cout << "Athlete Instance is destroyed."   << std::endl;
    }
    void show(){
        std::cout << "Sport Type   : " << sportType << std::endl;
        std::cout << "Athlete Name : " << getName() << std::endl;
        //std::cout << "Athlete Name : " << this->name << std::endl;  // <<- 좌측 코드 실행 시 에러 발생
    }   // name 멤버 변수는 Athlete class 의 멤버 변수가 아니라, 부모 class의 멤버 변수이다.
};      // 따라서 this 포인터로는 name 멤버 변수에 접근 불가하며, 부모 class 의 public 멤버 함수인 getName()을 통해 값을 반환받는다. 
    
class Athlete_Student : public Student, public Athlete{
public:
    Athlete_Student(std::string sportType, std::string name, int studentID)
                    : Person(name), Athlete(sportType, name), Student(studentID, name){
        std::cout << "Athlete_Student Instance is created."     << std::endl;
    }
    ~Athlete_Student(){
        std::cout << "Athlete_Student Instance is destroyed."   << std::endl;
    }
    void show(){std::cout << "Name : " << getName() << std::endl;}
};

int main(void){
    Athlete_Student golferStudent("Golf", "BS-Kim", 1001);
    golferStudent.show();       // 부모 class 인 Athlete Class 와 Student Class 모두 show() 멤버 함수를 갖고 있다.
                                // 자식 class 인 Athlete_Student 에서 show() 멤버 함수를 오버로딩하지 않았다면
                                // 멤버 함수가 모호(ambiguous)하다고 하며 컴파일 에러 발생하게 된다.
}

/*
출력 : 
Person Instance is created.
Student Instance is created.
Athlete Instance is created.
Athlete_Student Instance is created.
Name : BS-Kim
Athlete_Student Instance is destroyed.
Athlete Instance is destroyed.
Student Instance is destroyed.
Person Instance is destroyed.

해석 : 
main() 영역에서 손자 class 의 생성자를 1회 호출했을 뿐이지만,
조부모 class 부터, 부모 class, 그리고 자식 class 순으로 생성자가 호출된 것을 알 수 있다.
상속을 받으면 객체 (Instance) 내에 부모 class 의 멤버의 정보가 복사되어 생성되는 것이 아니라,
부모 class 의 객체가 따로 메모리 할당이 된다는 것을 알 수 있다.
두 부모 class 의 생성 순서 우선 순위는 잘 모르겠다.
자식 class 에서 부모 class 생성자 호출 순서와는 다르게 되었다.
프로그램이 종료되며 메모리 해제 시에는 생성자의 역순으로 소멸자가 실행되어
제일 상단의 조부모 class 가 마지막으로 메모리 해제된다.
*/