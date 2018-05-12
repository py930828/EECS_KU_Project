
public class ArrayHelper {
public void print2DArray(int[][] array)
{
	for(int i=0;i<array.length;i++)
	{
		for(int j=0;j<array[i].length;j++)
		{
			if(j==(array[i].length)-1)
			{
				System.out.print(array[i][j]);
			}
			else
			{
				System.out.print(array[i][j]+",");
			}
			
		}
		System.out.println("");
	}
}
public int arraySum(int[] array)
{
	int sum=0;
	for(int i=0;i<array.length;i++)
	{
		sum=sum+array[i];
	}
	return (sum);
}
public double arrayAvg(int[] array)
{
	double sum=0;
	double avg=0.0;
	for(int i=0;i<array.length;i++)
	{
		sum=sum+array[i];
	}
	avg=sum/(array.length);
	return (avg);
}
public int arrayMax2D(int[][] array)
{
	int k=0;
	for(int i=0;i<array.length;i++)
	{
		for(int j=0;j<array[i].length;j++)
		{
			if(k<array[i][j])
			{
				k=array[i][j];
			}
		}
	}
	return (k);
}
public int arraySum2D(int[][] array)
{
	int sum=0;
	for(int i=0;i<array.length;i++)
	{
		for(int j=0;j<array[i].length;j++)
		{
			sum=sum+array[i][j];
		}
	}
	return sum;
}
public double arrayAvg2D(int[][] array)
{
	double sum=0;
	double avg=0.0;
	for(int i=0;i<array.length;i++)
	{
		for(int j=0;j<array[i].length;j++)
		{
			sum=sum+array[i][j];
		}
	}
	avg=sum/(array.length*array[0].length);
	return avg;
}
}
