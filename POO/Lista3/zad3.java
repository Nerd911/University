public class zad3 {
  public class TaxCalculator {
    public Decimal CalculateTax( Decimal Price ) { return Price * 0.22 }
  }
  public class Item {
    public Decimal Price { get { ... } }
    public string Name { get { ... } }
  }
  public class CashRegister {
    public TaxCalculator taxCalc = new TaxCalculator();
    public Decimal CalculatePrice( Item[] Items ) {
      Decimal _price = 0;
      foreach ( Item item in Items ) {
        _price += itemPrice + taxCalc.CalculateTax( item.Price );
      }
      return _price;
    }
    public string PrintBill( Item[] Items ) {
      foreach ( var item in Items )
      Console.WriteLine( "towar {0} : cena {1} + podatek {2}",
      item.Name, item.Price, taxCalc.CalculateTax( item.Price ) );
    }
  }
}
