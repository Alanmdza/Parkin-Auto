#define TRIGGERA1 18
#define ECOA1 8
#define TRIGGERA2 3
#define ECOA2 46
#define TRIGGERA3 9
#define ECOA3 10
#define TRIGGERA4 11
#define ECOA4 12
#define TRIGGERA5 13
#define ECOA5 14

#define TRIGGERB1 17
#define ECOB1 16
#define TRIGGERB2 15
#define ECOB2 7
#define TRIGGERB3 6
#define ECOB3 5
#define TRIGGERB4 4
#define ECOB4 1
#define TRIGGERB5 2
#define ECOB5 42

#define TRIGGERC1 41
#define ECOC1 40
#define TRIGGERC2 39
#define ECOC2 38
#define TRIGGERC3 37
#define ECOC3 36
#define TRIGGERC4 35
#define ECOC4 0
#define TRIGGERC5 45
#define ECOC5 48

#define TRIGGERD1 47
#define ECOD1 21
#define TRIGGERD2 20
#define ECOD2 19

int obtenerEco(int numero)
{
    switch (numero)
    {
    case 0:
        return ECOA1;
    case 1:
        return ECOA2;
    case 2:
        return ECOA3;
    case 3:
        return ECOA4;
    case 4:
        return ECOA5;
    case 5:
        return ECOB1;
    case 6:
        return ECOB2;
    case 7:
        return ECOB3;
    case 8:
        return ECOB4;
    case 9:
        return ECOB5;
    case 10:
        return ECOC1;
    case 11:
        return ECOC2;
    case 12:
        return ECOC3;
    case 13:
        return ECOC4;
    case 14:
        return ECOC5;
    case 15:
        return ECOD1;
    case 16:
        return ECOD2;
    default:
        return 0; // Devuelve un valor por defecto para otros valores de numero
    }
}

int obtenerTrigger(int numero)
{
    switch (numero)
    {
    case 0:
        return TRIGGERA1;
    case 1:
        return TRIGGERA2;
    case 2:
        return TRIGGERA3;
    case 3:
        return TRIGGERA4;
    case 4:
        return TRIGGERA5;
    case 5:
        return TRIGGERB1;
    case 6:
        return TRIGGERB2;
    case 7:
        return TRIGGERB3;
    case 8:
        return TRIGGERB4;
    case 9:
        return TRIGGERB5;
    case 10:
        return TRIGGERC1;
    case 11:
        return TRIGGERC2;
    case 12:
        return TRIGGERC3;
    case 13:
        return TRIGGERC4;
    case 14:
        return TRIGGERC5;
    case 15:
        return TRIGGERD1;
    case 16:
        return TRIGGERD2;
    default:
        return 0; // Devuelve un valor por defecto para otros valores de numero
    }
}