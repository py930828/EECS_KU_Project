
public class MyCircle {
	//Define the constant PI.
    public static final double PI = 3.141592; //static variables are initialized outside of a constructor
   
    //The MyCircle class has one property: radius
    //Put a radius in your class
    public double radius;


    //The MyCircle class has methods too.

    //First create a constructor that sets the radius to 0.0.
          MyCircle ()
          {
        	  radius=0.0;
          }
          public void setRadius(double r)
          {
        	  radius=r;
          }
    //Make a method that calculates the diameter of a circle. Recall the radius is half of the diameter.
    //This method will take no parameters and return a double.
    //Why no parameters? Because the circle class has a radius built in. All methods in the Circle class have access to it without it being passed
    //as a parameter! Sweet!
            public double calcdiameter()
            {
            	double diameter;
            	diameter=2*radius;
            	return (diameter);
            }
    //Make a method that returns the area of a Circle.
    //This method takes no parameters.  It returns a double.
    //Recall the area of a circle is PI * radius * radius
    //Since our circle has PI and radius as properties, we can use those in our function without passing them in as parameters. Tubular!
            public double calcArea()
            {
            	double Area;
            	Area=PI*radius*radius;
            	return (Area);
            }
    

    //Make a method that returns the circumference of a Circle.
    //This method takes no parameters.  It returns a double.
    //Recall the circumference of a circle is 2 * PI * radius
    //Since our circle has PI and radius as properties, we can use those in our function without passing them in as parameters. Radical!
            public double calccircumference()
            {
            	double circumference;
            	circumference=2*PI*radius;
            	return (circumference);
            }
			
				
			}

