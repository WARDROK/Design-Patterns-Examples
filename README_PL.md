# Design-Patterns-Examples

## Prototype Design Pattern

**Prototype** pozwala na tworzenie nowych obiektów poprzez klonowanie istniejących instancji wraz z ich obecnym stanem, zamiast polegać na bezpośrednim wywoływaniu konstruktorów i towrzeniu odbiektów od zera. Dzięki temu możliwe jest uniknięcie kosztownej inicjalizacji obiektów.

**Przykład użycia:**

- Zamiast wielokrotnie przeprowadzać skomplikowaną inicjalizację (np. ładowanie danych z bazy, z pliku lub wykonywanie obliczeń), możesz stworzyć jeden wzorcowy obiekt (prototyp), a następnie klonować go w razie potrzeby. Dzięki temu zmiany w stanie prototypu automatycznie przenoszą się na nowo tworzone obiekty, co upraszcza zarządzanie i zwiększa wydajność aplikacji.

## Composite Design Pattern

**Composite** pozwala na traktowanie pojedynczych obiektów oraz grup obiektów w jednolity sposób. Dzięki temu można tworzyć struktury hierarchiczne, w których elementy (liście) oraz kompozyty (elementy złożone) są traktowane identycznie.

### Główne cechy:

- Tworzenie struktur drzewiastych.
- Traktowanie pojedynczych obiektów i ich kompozycji w identyczny sposób.
- Upraszcza kod klienta, który nie musi rozróżniać między elementem pojedynczym a grupą elementów.

## Design Pattern Adapter

**Adapter** umożliwia współpracę między interfejsami, które normalnie nie są ze sobą kompatybilne. Dzięki adapterowi możemy dostosować interfejs istniejącej klasy (Adaptee) do wymagań klienta, który oczekuje innego interfejsu (Target).

### Jak to działa:

- **Cel (Target):** Definiuje interfejs, który jest oczekiwany przez klienta.
- **Adaptowany (Adaptee):** Posiada przydatną funkcjonalność, lecz jego interfejs nie pasuje do interfejsu Target.
- **Adapter obiektowy (Object Adapter):** Używa kompozycji. Adapter posiada instancję klasy Adaptee i tłumaczy wywołania metod z interfejsu Target na metody klasy Adaptee.
- **Adapter klasowy (Class Adapter):** Oparty na dziedziczeniu. Adapter dziedziczy zarówno po interfejsie Target, jak i po Adaptee, dzięki czemu może bezpośrednio wywoływać metody Adaptee.

## Wzorzec Proxy: Virtual Proxy oraz Copy-on-Write Proxy

**Proxy** umożliwia kontrolowanie dostępu do obiektu poprzez wstawienie warstwy pośredniczącej. Poniżej przedstawiono dwa typy proxy:

1. **Virtual Proxy**  
   Umożliwia leniwą (lazy) inicjalizację obiektu – obiekt, który jest kosztowny w utworzeniu, nie jest tworzony, dopóki nie jest faktycznie potrzebny. Dzięki temu możliwe jest oszczędne wykorzystanie zasobów.

2. **Copy-on-Write Proxy**  
   Umożliwia współdzielenie obiektu dla operacji odczytu, a przy próbie modyfikacji wykonuje jego głęboką kopię, o ile obiekt jest współdzielony. Pozwala to na wydajne zarządzanie pamięcią, modyfikując tylko te instancje, które rzeczywiście potrzebują zmiany.

### Jak to działa:

- **Virtual Proxy:**  
  Przechowuje prywatny wskaźnik `resource_` do zasobu (`ExpensiveResource`), który jest tworzony dopiero w momencie pierwszego wywołania metody.

- **Copy-on-Write Proxy:**  
  Przechowuje prywatny wskaźnik `resource_` do współdzielonego obiektu (`Document`) przy użyciu `std::shared_ptr`. Podczas modyfikacji, jeśli obiekt jest współdzielony (tj. referencji > 1), tworzona jest kopia obiektu, aby operacja modyfikacji nie wpłynęła na inne instancje.

## Wzorzec Obserwator

**Obserwator** (Observer Pattern) umożliwia zdefiniowanie relacji jeden-do-wielu między obiektami, tak aby zmiana stanu jednego obiektu (Subject) była automatycznie przekazywana do wszystkich jego zależnych (Observer). Jest to szczególnie przydatne w implementacji mechanizmów powiadamiania i synchronizacji, na przykład w interfejsach użytkownika czy systemach zdarzeń.

### Jak to działa:

- **Subject (Podmiot):** Przechowuje listę obserwatorów oraz udostępnia metody umożliwiające ich rejestrację lub wyrejestrowanie. Gdy nastąpi zmiana stanu, Subject powiadamia wszystkich zarejestrowanych obserwatorów.
- **Observer (Obserwator):** Interfejs definiujący metodę, która ma być wywołana, gdy Subject zmienia swój stan. Klasy implementujące ten interfejs wykonują określone działania w odpowiedzi na powiadomienie.
- **Powiadomienie:** Gdy Subject zmienia swój stan, wywołuje metodę powiadamiającą, która iteruje po liście obserwatorów i przekazuje im nowe dane lub informację o zmianie.

## Wzorzec Komenda (Command Pattern)

**Komenda** polega na opakowaniu żądania jako obiektu. Pozwala to na przekazywanie, przechowywanie oraz opóźnione wykonanie poleceń, co daje możliwość kolejkowania operacji, zapisywania ich w logach, czy też implementacji mechanizmu cofania (undo).

### Ogólna idea:

- **Encapsulation of requests:**  
  Żądanie (np. wywołanie metody) zostaje zamknięte wewnątrz obiektu, który przechowuje wszystkie niezbędne parametry do wykonania operacji.
- **Decoupling:**  
  Wywołujący (Invoker) nie musi znać szczegółów implementacji operacji – jedynie polega na interfejsie komendy. Dzięki temu łatwo jest zmieniać zachowanie systemu poprzez podstawianie innych implementacji komend.
- **Elastyczność:**  
  Komendy można przechowywać, przekazywać oraz wywoływać w dowolnym momencie, co umożliwia tworzenie bardziej elastycznych i rozszerzalnych architektur.

## Wzorzec Dekorator (Decorator Pattern)

**Dekorator** pozwala na dynamiczne rozszerzenie funkcjonalności obiektu poprzez opakowywanie go dodatkowymi komponentami dekoratorowymi, bez zmiany jego interfejsu. Dzięki temu można dodawać nowe funkcjonalności do obiektu w trakcie działania programu, bez ingerencji w jego strukturę.

### Ogólna idea:

- **Podstawa:**  
  Tworzona jest wspólna klasa bazowa (interfejs) reprezentująca obiekt, który ma być dekorowany (np. `Coffee`).
- **Komponent:**  
  Klasa implementująca interfejs (np. `SimpleCoffee`) – dostarcza podstawowe funkcjonalności.
- **Dekorator:**  
  Klasa abstrakcyjna (`CoffeeDecorator`) implementująca interfejs, która zawiera wskaźnik do obiektu typu bazowego. Dekoratory dziedziczą z tej klasy i rozszerzają zachowanie, dodając nowe cechy (np. `MilkDecorator`, `SugarDecorator`).
