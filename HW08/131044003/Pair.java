
import java.util.Objects;

public class Pair<F,S>
{	
	private F first;
	private S second;

	public Pair(F firstE,S secondE)
	{
		setFirst(firstE);
		
		setSecond(secondE);
	}


    public boolean equals(Object o) 
    {
	    if (!(o instanceof Pair)) 
	    	return false;

	    Pair otherPair = (Pair) o;

	    return this.first.equals(otherPair.getFirst()) &&
	           this.second.equals(otherPair.getSecond());
  	}

    public int hashCode() 
    { 
    	return first.hashCode() ^ second.hashCode();
    }

	// setters
	public void setFirst(F firstE)
	{
		this.first=firstE;
	}

	public void setSecond(S secondE)
	{
		this.second=secondE;
	}

	// getters
	public F getFirst()
	{
		return first;
	}

	public S getSecond()
	{
		return second;
	}


}