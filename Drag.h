#ifndef DRAG_H_INCLUDED
#define DRAG_H_INCLUDED

float quality (float x, float l, float h)
{
    return (x - l) / (h - l);
}

float eval_q (float q, float l, float h)
{
    return l + (h - l) * q;
}

float interp_table (float x, float xtable[], float ytable[], unsigned int n)
{
    unsigned int nlower = 0;

    while (nlower < n - 1 && x > xtable[nlower + 1])
    {
        nlower++;
    }

    return eval_q (quality (x, xtable[nlower], xtable[nlower + 1]), ytable[nlower], ytable[nlower + 1]);
}

float Cd_Sphere (float Re)
{
    float xtable[] = { -1.0f, 3.0f, log10f (4.0f) + 5.0f, log10f (4.0f) + 5.0f, 7.0f, 8.0f };
    float ytable[] = { 250.0f, 0.4f, 0.4f, 0.1f, 0.4f, 0.4f };
    unsigned int n = 6;

    if (Re <= 0.0f)
    {
        return 0.0f;
    }
    else
    {
        float lRe = log10 (Re);
        return interp_table (lRe, xtable, ytable, n);
    }
}

#endif // DRAG_H_INCLUDED
