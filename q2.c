#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    if (planet > totalPlanets || fuel <= 0) return;
    else {
        fuel = fuel - consumption + recharge + solarBonus;
        printf("Planet %d: Remaining fuel = %d\n", planet, fuel);
        planet++;
        calculateFuel(fuel, consumption, recharge, solarBonus, planet, totalPlanets);
    }
}
int main() {
    calculateFuel(100, 7, 10, 5, 1, 5);
    return 0;
}