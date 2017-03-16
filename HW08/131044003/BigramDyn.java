





public class BigramDyn<G> implements Bigram<G> 
{	
	private int dataType;

	public BigramDyn(int typeOfData) 
	{ 
		dataType=typeOfData;
		System.out.println("Doesnt have BigramDyn implemantation :(");
	}


	public void readFile(String fileName) throws Exception { } // read the all data from file

	public int numGrams()
	{
		int i=0;

		return i;
	}

	public int numOfGrams(G element1,G element2)
	{
		int i=0;

		return i;
	}


	public String toString()
	{
		String empty="Doesnt have toString method implemantation :(";

		return empty;
	}

}	