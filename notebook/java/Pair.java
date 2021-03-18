package modules;

/**
 * Created by triveni on 6/7/17.
 */
public class Pair<A, B> {
	public A X;
	public B Y;

	public Pair(A first, B second) {
		super();
		this.X = first;
		this.Y = second;
	}

	public int hashCode() {
		int hashFirst = X != null ? X.hashCode() : 0;
		int hashSecond = Y != null ? Y.hashCode() : 0;

		return (hashFirst + hashSecond) * hashSecond + hashFirst;
	}

	public boolean equals(Object other) {
		if (other instanceof Pair) {
			Pair otherPair = (Pair) other;
			return
					((  this.X == otherPair.X ||
							( this.X != null && otherPair.X != null &&
									this.X.equals(otherPair.X))) &&
							(  this.Y == otherPair.Y ||
									( this.Y != null && otherPair.Y != null &&
											this.Y.equals(otherPair.Y))) );
		}

		return false;
	}

	public String toString()
	{
		return "(" + X + ", " + Y + ")";
	}
}
