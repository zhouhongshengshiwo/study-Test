object是所有类的根类，Object类型可以表示任何类型的对象。

spring在开发中的作用
    -在java程序中，要不断的去创建对象，正常创建对象，我们会通过传统new的方式
        - new Student();
        - 设计模式(降低程序间的耦合(依赖))
        - java中还有另外一种创建对象的方式
            -反射机制
    -spring可以看成是一个工厂(一个容器)，在程序运行期间，spring会扫描核心配置文件中的
    内容，扫描bean标签中的id属性和class属性
        -id 组件的唯一标识
        -class 一个类的权限定类名(spring在底层会基于反射机制来创建java对象)
            -这样做的目的是为了降低程序间的耦合

要模拟spring的底层
    -需求:
        -创建web端架构的三层，保证每一层都能够调通

        
```java
import org.springframework.context.support.ClassPathXmlApplicationContext;
public class SpringTest02 {

    public static void main(String[] args) {
        //传统方式创建对象

        Student student = new Student();
        //java反射创建对象
        class aclass =Class.forName("com.eagles.pojo.Student");
        //基于字节码对象创建学生对象
        Student stu=(Student)aclass.newInstance();
    }


}
```

# java三层架构

- 表现层servlet：负责展现信息给用户，一般是jsp页面
- 业务层service：负责处理业务逻辑，一般是service层
- 数据层dao：负责存储数据，一般是dao层

package com.eagles.account.servlet;
import com.eagles.account.service.AccountService;
# 表现层
```java
public class AccountServlet {//表现层

    private AccountService accountService;//引用持有层，这里为什么不用new AccountService()呢？
//因为这样会产生类与类之间的依赖，耦合度太高，不利于代码的维护和扩展。
    public void setAccountService(AccountService accountService) {
        this.accountService = accountService;
    }

    public void saveAccount(){

        accountService.saveAccount();
    }

}
```
spring使用beans.xml配置文件来配置对象，并通过ClassPathXmlApplicationContext来加载配置文件。
这样可以解除类与类之间的依赖，提高代码的可维护性和扩展性。
```xml
<bean id="servlet" class="com.eagles.account.servlet.AccountServlet">
        <property name="accountService" ref="service"></property>
        <!--ref引用别的bean作为属性(property标签)-->
    </bean>

    <bean id="service" class="com.eagles.account.service.AccountService">
        <property name="accountDao" ref="dao"></property>
    </bean>

    <bean id="dao" class="com.eagles.account.dao.AccountDao">
    </bean>
    ```
