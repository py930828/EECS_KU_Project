
public class HangMan {
	private String secret_word;
	public char[] disguised_word;
	private int guessCount;
	private int missesCount;
	private int MAX_MISSES_ALLOWED;
	private char[] missedMarkers;
	private static int gamesPlayed;

	public HangMan(String word,String dw)
	{
		secret_word=word;
		disguised_word=dw.toCharArray();
		guessCount=0;
		missesCount=0;
		MAX_MISSES_ALLOWED=7;
		missedMarkers=new char[7];
		for(int i=0;i<missedMarkers.length;i++)
		{
			missedMarkers[i]='0';
		}
	}
	
	public boolean guessCharacter(char X)
	{
		char x;
		x=Character.toLowerCase(X);
		boolean flag = false;
		for(int i=0;i<secret_word.length();i++)
		{
			if(x==secret_word.charAt(i))
			{
				disguised_word[i]=x;
				flag = true;
			}
		}
		if(flag==true)
		{
			guessCount++;
			return true;
		}
		else
		{
			guessCount++;
			missesCount++;
			missedMarkers[missesCount-1]='X';
			return false;
		}
	}
	public boolean isGameOver()
	{
		if(missesCount==MAX_MISSES_ALLOWED||getDisguisedWord().equals(secret_word))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	public boolean isFound()
	{
		if(getDisguisedWord().equals(secret_word))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	public String getDisguisedWord()
	{
		String getDisguisedWord="";
		for(int i=0;i<disguised_word.length;i++)
		{
			getDisguisedWord=getDisguisedWord+disguised_word[i];
		}
		return (getDisguisedWord);
	}
	public int getGuessCount()
	{
		int getGuessCount=0;
		getGuessCount=guessCount;
		return getGuessCount;
	}
	public int getMissesCount()
	{
		int getMissesCount=0;
		getMissesCount=missesCount;
		return getMissesCount;
	}
	public String getMissedMarker()
	{
		String getMissedMarker;
		getMissedMarker="";
		for(int i=0;i<missedMarkers.length;i++)
		{
			getMissedMarker=getMissedMarker+missedMarkers[i];
		}
		return (getMissedMarker);
	}
	public void GamePlayed()
	{
		if(isGameOver()==true)
		{
			gamesPlayed=gamesPlayed+1;
		}
	}
	public int get_gamesPlayed()
	{
		return (gamesPlayed);
	}
}
