import numpy as np
import matplotlib.pyplot as plt

[R,V] = np.genfromtxt("RadialVelocities.dat", delimiter=" ", unpack=True, skip_header=1)
caminata = np.genfromtxt("caminata_aleatoria.tarea", delimiter=",", skip_header=1)
[Md,Mb,Mh,l] = caminata[-1,:]
bb = 0.2497
bd = 5.16
ad = 0.3105
ah = 64.3


R_lin = np.linspace(np.min(R), np.max(R), 200)
bulbo = Mb**0.5*R_lin/(R_lin**2+bb**2)**0.75
disco = Md**0.5*R_lin/(R_lin**2+(bd+ad)**2)**0.75
halo = Mh**0.5/(R_lin**2+ah**2)**0.25
V_lin = bulbo + disco + halo

fig, ax = plt.subplots()
ax.plot(R,V, '.', label='Datos Experimentales')
ax.plot(R_lin,V_lin, label='Modelo $M_b='+str(Mb)[0:6]+'$ $M_d='+str(Md)[0:6]+'$ $M_h='+str(Mh)[0:6]+'$')
ax.set_xlabel('Radio [kpc]')
ax.set_ylabel('Velocidad [km/s]')
ax.set_ylim([np.min(V), np.max(V)])
ax.set_xlim([np.min(R), np.max(R)])
ax.grid()
ax.legend(loc='best')
print("Guardando Figura")
fig.savefig("v_exp_mod.png")
