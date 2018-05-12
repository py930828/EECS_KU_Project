import java.util.Scanner;
public class MyCircleTest {
	public static void main(String[] args) {
		
        // Declare a new circle called myCircle
        // Declare any other variables you need (e.g. Scanner, double)
		MyCircle circle1=new MyCircle();
        //Get a radius from the user
       Scanner myScan=new Scanner(System.in);
       double r=myScan.nextDouble();
        //Display a message to the screen that says "My circle has a radius of <put the radius here>"
       System.out.println("My circle has a radius of "+r);
        //Use the method area() from myCircle to print the area                         
       circle1.setRadius(r);
       System.out.println(circle1.calcArea());
        //Use the method circumference() from myCircle to print the circumference
       System.out.println(circle1.calccircumference());
        //Using only a method call to diameter()  to print the diameter
       System.out.println(circle1.calcdiameter());
}
}
