import java.util.Scanner;
public class GameDriver {

	public static void main(String[] args) {
		String Y;
		String S="big bang";
		int G=0;
		String P;
		P=("Welcome to the Hangman Game!"+"\n"+"---------------"+"\n"+"\n"+"\n");
		System.out.print(P);
		char X;
		Scanner myScan=new Scanner(System.in);
		do
		{
			String N="";
			for(int i=0;i<S.length();i++)
			{
				if(S.charAt(i)==' ')
				{
					N=N+" ";
				}
				else
				{
					N=N+"?";
				}
					
			}
			HangMan game=new HangMan(S,N);
			do
			{
				System.out.println("Guess this: "+game.getDisguisedWord());
				System.out.println("Guesses so far: "+game.getGuessCount());
				System.out.println("Miesses: "+game.getMissedMarker());
				System.out.print("Enter your guess character: ");
				X=myScan.next().charAt(0);
				game.guessCharacter(X);
				System.out.println("");
			}while(game.isGameOver()==false);
			game.GamePlayed();
			if(game.isFound()==true)
			{
				String z=("Game Over!"+"\n"+"Congratulations! You guessed the secret word: "+S+" in "+game.getGuessCount()+" guesses!"+"\n"+"Do you want to play again? (yes/no):");
				System.out.println(z);
			}
			else
			{
				String z=("Game Over!"+"\n"+"You died. "+"Next time, guess as if your life depended on it."+"Do you want to play again? (yes/no):"+"\n");
				System.out.println(z);
			}
			Scanner myScanner=new Scanner(System.in);
			Y=myScanner.nextLine();
			if(Y.equals("yes"))
			{
				System.out.print("Input a new secret word: ");
				S=myScanner.nextLine();
			}
			else
			{
				G=game.get_gamesPlayed();
			}
		}while(Y.equalsIgnoreCase("yes"));
		System.out.println("Thank you playing "+G+" game(s) of Hang Man!");
		

	}

}
