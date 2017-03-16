




import java.io.*;

import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;





public class BigramMap<G> implements Bigram<G>
{
	private int dataType;

	private int numOfBigrams;

	private Scanner input;

	private Map< Pair<G,G> ,Integer> data;

	//////// public ////////
	public BigramMap() {  /* delibaretely empty*/  } // no paramater constructor

	public BigramMap(int typeOfData) 
	{ 
		dataType=typeOfData;
		data=new HashMap<Pair<G,G> ,Integer>();
	}

	public void readFile(String fileName) throws Exception
	{	
		try
		{
			input=new Scanner(new File(fileName));
		}
		catch(FileNotFoundException exception)
		{
			System.err.println("File couldnt be opened!");
			throw new Exception();
		}

		List<G> dataTemp= new ArrayList<G>();

		// reading data from file and adding them into arraylist
		while(input.hasNext())
		{
			dataTemp.add((G)input.next());
		} 

		numOfBigrams=dataTemp.size()-1;

		
		// adding the bigrams into map
		for(int i=0; i< dataTemp.size()-1; ++i)
		{	
			Pair<G,G> myPair= new Pair<G,G>(dataTemp.get(i),dataTemp.get(i+1));

			// if bigram already exists increase value by one
			if(data.containsKey(myPair))
			{
				int count=data.get(myPair);

				data.put(myPair,count+1);
			} // if bigram doent exist add it to the map
			else
				data.put(myPair,1);
		} 


	} //end of readFile func

	// numGrams func gonna return the number of the calculated bigrams
	public int numGrams() { return numOfBigrams; } // inline implemantation

	// this is gonna takes two elements and  
	public int numOfGrams(G element1,G element2)
	{
		int found=0;

		Pair<G,G> myPair= new Pair<G,G>(element1,element2);

		if(data.containsKey(myPair))
		{
			found=data.get(myPair);
		}

		return found;

	} // end of numOfGrams func


	public String toString()
	{
		String empty="Doesnt have toString method implemantation :(";

		return empty;
	}





}