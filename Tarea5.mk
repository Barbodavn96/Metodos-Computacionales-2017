
Results_hw5.pdf: v_exp_mod.png
	pdflatex Results_hw5.tex

v_exp_mod.png: caminata_aleatoria.tarea
	python Plots.py

caminata_aleatoria.tarea: CurvaRotacion.c
	gcc CurvaRotacion.c -lm -o CurvaRotacion.x
	./CurvaRotacion.x
	tail -10 caminata_aleatoria.tarea

clean:
	rm *.tarea *.png *.log *.aux