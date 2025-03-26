# Falling-Void Coding Standards

## Classes Names

Class name just be descriptive and describe the module they contain. 

Class names must be in Pascal Case and must contain the prefix FV to distinguish from Unreal Engine classes for example `FVPlayerBase.h`. 

Class Names for Behaviour Tree must be prefixed with `BT` for example `FVBTAttackPlayer.h`

## Variables

UPROPERTY variables should follow the Unreal Engine nameing convection.

Each UPROPERTY generic variable types like float, int and bools must be iniatlized with {}. Unreal Object Types can be left blank. 

Private variables should be prefix `m_` followed by Pascal Case. 

temporary variables should be camel case. 

Example
```cpp
    UPROPERTY()
    float Health {100.0f}

    //private
    float m_CurrentHealth; 

    //Function
    void TakeDamage(float damage)
    {
        float newHealth = m_CurrentHealth - damage;
        ...
    }
```

## Functions

Functions should be named Pascal Case. 

Blueprint Events must prefix with On for example `OnDied()`

## Enums

Enums should be prefix with E for example `EPlayerState`
