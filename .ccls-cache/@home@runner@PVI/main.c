#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double exato(double x) { return }

double f(double x, double y) { return (double)(2 - 2 * x * y) / (x * x + 1); }

double euler(double x1, double y1, double h) { return h * f(x1, y1); }

double eulermod(double x1, double y1, double h) {
  double dy = f(x1 + h, y1 + h * f(x1, y1));
  return (h / 2.0) * (f(x1, y1) + dy);
}

double rk4(double x1, double y1, double h) {
  double k1, k2, k3, k4;
  k1 = f(x1, y1);
  k2 = f(x1 + h / 2.0, y1 + h * k1 / 2.0);
  k3 = f(x1 + h / 2.0, y1 + h * k2 / 2.0);
  k4 = f(x1 + h, y1 + h * k3);
  return (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
}

int main(void) {
  double h = 1, x = 0, ym, ye, yrk, ex, m1, m2, m3;
  double listaH[14], listaErrosEuler[14], listaErrosEM[14], listaErrosRK4[14];
  int i;
  FILE *arq;
  arq = fopen("dados.dat", "w");
  m1 = m2 = m3 = 0;
  for (i = 0; i < 14; i++) {
    ye = ym = yrk = 1;
    h /= 2.0;
    for (x = 0; x <= 1.1; x += h) {
      ex = exato(x + h);
      ye += euler(x, ye, h);
      ym += eulermod(x, ym, h);
      yrk += rk4(x, yrk, h);
    }
    printf("\nh = %lf ", h);
    printf("\nErroEuler = %g \nErroEulerMod = %g \nErroRK4 = %g\n\n\n",
           fabs(ye - ex), fabs(ym - ex), fabs(yrk - ex));
    fprintf(arq, "%g %g %g %g\n", log10(h), log10(fabs(ye - ex)),
            log10(fabs(ym - ex)), log10(fabs(yrk - ex)));
    listaH[i] = log10(h);
    listaErrosEuler[i] = log10(fabs(ye - ex));
    listaErrosEM[i] = log10(fabs(ym - ex));
    listaErrosRK4[i] = log10(fabs(yrk - ex));
  }
  /*
    O código abaixo teve como intuito aproximar os coeficientes angulares das
    retas que consistem nos gráficos log log dos erros em função de h. A
    variável m1 representa o coeficiente angular da equação log-log pelo método
    de Euler, e m2 pelo método de Euler modificado. Os coeficientes angulares
    obtidos são, com uma boa aproximação, valores inteiros. Tais valores são as
    respectivas potências de h na função E(h).
  */

  for (i = 0; i < 13; i++) {
    m1 += (listaErrosEuler[i + 1] - listaErrosEuler[i]) /
          (listaH[i + 1] - listaH[i]);
    m2 += (listaErrosEM[i + 1] - listaErrosEM[i]) / (listaH[i + 1] - listaH[i]);
  }
  m1 = m1 / 13.0;
  m2 = m2 / 13.0;
  printf("\n\nPotências de h para Euler e Euler mod.: \nm1 = %ld\nm2 = %ld",
         lround(m1), lround(m2));
  for (i = 0; i < 9; i++) {
    m3 +=
        (listaErrosRK4[i + 1] - listaErrosRK4[i]) / (listaH[i + 1] - listaH[i]);
  }
  m3 = m3 / 9.0;
  printf("\n\nPotência de h para RK4: \nm3 = %ld", lround(m3));
  /*
    Para o método de Runge Kutta de quarta ordem, há uma forte discrepância do
    gráfico de erros para valores muito pequenos de h com relação ao resto. Por
    isso não convém aproximar o coeficiente angular usando todos os pontos da
    curva. Para valores de h não tão pequenos, encontramos 4 como sendo o tal
    coeficiente.
  */
  return 0;
}g\n\n\n",
           fabs(ye - ex), fabs(ym - ex), fabs(yrk - ex));
fprintf(arq, "%g %g %g %g\n", log10(h), log10(fabs(ye - ex)),
        log10(fabs(ym - ex)), log10(fabs(yrk - ex)));
listaH[i] = log10(h);
listaErrosEuler[i] = log10(fabs(ye - ex));
listaErrosEM[i] = log10(fabs(ym - ex));
listaErrosRK4[i] = log10(fabs(yrk - ex));
}
/*
  O código abaixo teve como intuito aproximar os coeficientes angulares das
  retas que consistem nos gráficos log log dos erros em função de h. A
  variável m1 representa o coeficiente angular da equação log-log pelo método
  de Euler, e m2 pelo método de Euler modificado. Os coeficientes angulares
  obtidos são, com uma boa aproximação, valores inteiros. Tais valores são as
  respectivas potências de h na função E(h).
*/

for (i = 0; i < 13; i++) {
  m1 += (listaErrosEuler[i + 1] - listaErrosEuler[i]) /
        (listaH[i + 1] - listaH[i]);
  m2 += (listaErrosEM[i + 1] - listaErrosEM[i]) / (listaH[i + 1] - listaH[i]);
}
m1 = m1 / 13.0;
m2 = m2 / 13.0;
printf("\n\nPotências de h para Euler e Euler mod.: \nm1 = %ld\nm2 = %ld",
       lround(m1), lround(m2));
for (i = 0; i < 9; i++) {
  m3 += (listaErrosRK4[i + 1] - listaErrosRK4[i]) / (listaH[i + 1] - listaH[i]);
}
m3 = m3 / 9.0;
printf("\n\nPotência de h para RK4: \nm3 = %ld", lround(m3));
/*
  Para o método de Runge Kutta de quarta ordem, há uma forte discrepância do
  gráfico de erros para valores muito pequenos de h com relação ao resto. Por
  isso não convém aproximar o coeficiente angular usando todos os pontos da
  curva. Para valores de h não tão pequenos, encontramos 4 como sendo o tal
  coeficiente.
*/
return 0;
}