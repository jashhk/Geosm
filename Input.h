#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
    Input( double _delta , double _LCG   , double _VCG ,
           double _b     , double _beta  , double _V   ,
           double _trim0 , double _trim1 , double _trim2 )
    {
        delta = _delta;
        LCG = _LCG;
        VCG = _VCG;
        b = _b;
        beta = _beta;
        V = _V;
        trim[0] = _trim0;
        trim[1] = _trim1;
        trim[2] = _trim2;
    }

    double get_Delta() { return delta; }
    double get_LCG() { return LCG; }
    double get_VCG() { return VCG; }
    double get_b() { return b; }
    double get_beta() { return beta; }
    double get_V() { return V; }
    double get_trim0() { return trim[0]; }
    double get_trim1() { return trim[1]; }
    double get_trim2() { return trim[2]; }

private:
    double delta; // Total Weight , pounds
    double LCG; //Longitudinal Center of Gravity, ft forward of transom
    double VCG; //Vertical Center of Gravity, feet above Baseline
    double b; // Chine beam length , feet
    double beta; // Deadrise angle
    double V; // Speed , foot / sec
    double trim[3]; // trim angle2 , 2<=trim<=24
};

#endif // INPUT_H

//
