interface是对应层与上一层的接口，它定义了上一层所需的服务，并对下一层提供服务。

# serviceImpl01
```java
@Service("accountService01")//标识该类是一个Spring的Bean，并指定Bean的名称，也可以不注释，直接用类名作为Bean的名称，在主函数调用时，注解的首字母记得切换成小写字母

public class AccountServiceImpl implements AccountService {

    @Resource(name = "dao")//依赖注入类实例
    @Autowired//自动识别类实例注入
    private AccountDao accountDao;

    @Override//@Override 注解用来指示一个方法是重写了父类或接口中的某个方法。
    public void saveAccount() {
        accountDao.saveAccount();
    }
}
```

@Autowired//自动实例注入，检测容器里面的实例注入,但是有多分实例时，会报错，在注册名字时区别开就行
    @Qualifier("accountService01")//指定实例注入，防止实例冲突报错
# test
```java
public class SpringTest {

    public static void main(String[] args) {

        //创建容器对象
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("/beans/beans.xml");

        //取出表现层的实例
        AccountController accountController = (AccountController)context.getBean("accountController");//取出注解或者类名作为Bean的名称
        Student stu = (Student)context.getBean("student");//取出注解或者类名作为Bean的名称
        System.out.println(accountController);
        System.out.println(stu);
        accountController.saveAccount();

    }

}
```
