
import java.io.*;


public interface Bigram <G> 
{
	public void readFile(String fileName) throws Exception; // read the all data from file

	public int numGrams(); // calculate all bigrams and return it

	public int numOfGrams(G element1,G element2); // return the number of the bigram according to parameters

	public String toString(); // print out the bigrams
}