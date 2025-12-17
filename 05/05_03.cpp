///////////////////////////////////////////////////////////////////////

#include <print>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////

class GameComponent {
public:
  virtual ~GameComponent() = default;

  // -------------------------------------------------------------------

  virtual void execute_turn() = 0;

  virtual void add(GameComponent *) {}
};

///////////////////////////////////////////////////////////////////////

class Unit : public GameComponent {
public:
  void set_name(std::string_view name) { m_name = name; }
  void set_health(int health) { m_health = health; }
  void set_damage(int damage) { m_damage = damage; }

  // -------------------------------------------------------------------

  void execute_turn() override {
    if (m_health <= 0) {
      std::print("{} is dead and cannot act.\n", m_name);
      return;
    }

    prepare();
    action();
    teardown();
  }

protected:
  virtual void prepare() const = 0;

  virtual void action() const {
    std::print("{} deals {} damage.\n", m_name, m_damage);
  }

  virtual void teardown() const = 0;

  std::string m_name;
  int m_health = 0;
  int m_damage = 0;
};

///////////////////////////////////////////////////////////////////////

class Infantry : public Unit {
protected:
  void prepare() const override { std::print("[{}] draws sword.\n", m_name); }

  void teardown() const override {
    std::print("[{}] raises shield.\n", m_name);
  }
};

///////////////////////////////////////////////////////////////////////

class Artillery : public Unit {
protected:
  void prepare() const override {
    std::print("[{}] calibrates coordinates.\n", m_name);
  }

  void action() const override {
    std::print("{} deals {} damage.\n", m_name, m_damage);
  }

  void teardown() const override {
    std::print("[{}] reloads ammunition.\n", m_name);
  }
};

///////////////////////////////////////////////////////////////////////

class Squad : public GameComponent {
public:
  ~Squad() {
    for (auto component : m_components) {
      delete component;
    }
  }

  // -------------------------------------------------------------------

  void add(GameComponent *component) override {
    m_components.push_back(component);
  }

  // -------------------------------------------------------------------

  void execute_turn() override {
    std::print("--- Squad Command: Group Attack Begin ---\n");

    for (auto component : m_components) {
      component->execute_turn();
    }

    std::print("--- Squad Command: Group Attack End ---\n");
  }

private:
  std::vector<GameComponent *> m_components;
};

///////////////////////////////////////////////////////////////////////

class UnitBuilder {
public:
  virtual ~UnitBuilder() = default;

  void create_unit() { m_unit = create_instance(); }

  virtual void build_stats() = 0;
  virtual void build_identity() = 0;

  Unit *get_unit() { return m_unit; }

protected:
  virtual Unit *create_instance() = 0;
  Unit *m_unit = nullptr;
};

///////////////////////////////////////////////////////////////////////

class InfantryBuilder : public UnitBuilder {
public:
  void build_stats() override {
    m_unit->set_health(100);
    m_unit->set_damage(15);
  }

  void build_identity() override { m_unit->set_name("Knight"); }

protected:
  Unit *create_instance() override { return new Infantry; }
};

///////////////////////////////////////////////////////////////////////

class ArtilleryBuilder : public UnitBuilder {
public:
  void build_stats() override {
    m_unit->set_health(50);
    m_unit->set_damage(100);
  }

  void build_identity() override { m_unit->set_name("Catapult"); }

protected:
  Unit *create_instance() override { return new Artillery; }
};

///////////////////////////////////////////////////////////////////////

class Barracks {
public:
  Unit *recruit_unit(UnitBuilder &builder) {
    builder.create_unit();
    builder.build_stats();
    builder.build_identity();
    return builder.get_unit();
  }
};

///////////////////////////////////////////////////////////////////////

int main() {

  Barracks barracks;
  InfantryBuilder infantry_builder;
  ArtilleryBuilder artillery_builder;

  // -------------------------------------------------------------------

  GameComponent *army = new Squad;

  // -------------------------------------------------------------------

  GameComponent *vanguard = new Squad;

  // -------------------------------------------------------------------

  Unit *knight1 = barracks.recruit_unit(infantry_builder);
  knight1->set_name("Knight 1");

  Unit *knight2 = barracks.recruit_unit(infantry_builder);
  knight2->set_name("Knight 2");

  Unit *catapult = barracks.recruit_unit(artillery_builder);

  // -------------------------------------------------------------------

  vanguard->add(knight1);
  vanguard->add(knight2);

  army->add(vanguard);
  army->add(catapult);

  // -------------------------------------------------------------------

  std::print(">>> GAME TURN START <<<\n");

  army->execute_turn();

  std::print(">>> GAME TURN END <<<\n");

  // -------------------------------------------------------------------

  delete army;
}

///////////////////////////////////////////////////////////////////////
