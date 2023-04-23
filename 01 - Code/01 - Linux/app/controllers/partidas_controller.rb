class PartidasController < ApplicationController
  def new
    @competencia = Competencia.find(params[:competencia_id])
    @partida = @competencia.partidas.build
    @nadadores = Nadador.find(:all, :order => "apellido")
  end
  
  def create
    @competencia = Competencia.find(params[:competencia_id])
    @partida = @competencia.partidas.build(params[:partida])
    @partida.laps = params[:partida][:laps]    
    @partida.show_or_wait=false
   # tiempo_a_0
    if @partida.save
      flash[:success] = "La partida #{@partida.id} se ha creado correctamente."
      redirect_to competencia_path(@competencia)
    else
      flash[:error] = "La partida no se ha podido crear. Por favor, intentelo nuevamente."
      redirect_to root_path
    end
  end
  
  def index
    @competencia = Competencia.find(params[:competencia_id])
    @partidas = @competencia.partidas
  end
  
  def destroy
   # @competencia = Competencia.find(params[:competencia_id])
    @partida = Partida.find(params[:id])
    @competencia = @partida.competencia
    @partida.destroy
    flash[:error] = "La partida #{@partida.id} ha sido borrada"
    redirect_to competencia_path(@competencia)
  end
  
  def show
    @partida = Partida.find(params[:id])
    @competencia = @partida.competencia
    if @partida.show_or_wait==false
      #debo enviar el numero de laps a la unidad central para que pueda arrancar a contar tiempo
      mi_archivo = 'buffer_Tx.txt'
      fh = File.open( mi_archivo , 'w' )
      fh.puts("#{@partida.laps}")
      #informo que andariveles se van a usar
      if @partida.nadador_id_1 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_2 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_3 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_4 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_5 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_6 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_7 != nil then fh.puts(1) else fh.puts(0) end
      if @partida.nadador_id_8 != nil then fh.puts(1) else fh.puts(0) end
      fh.rewind
      fh.close
      #llamo a programa intercambio para mandar el numero de laps a la unidad central
      system("./intercambio")

    end
  end
  
  def wait
      @partida = Partida.find(params[:partida_id])
      @competencia = @partida.competencia
      if @partida.show_or_wait==true
        flash[:notice]="Partida ejecutada."
        return nil
      end   
         
      # llamo al programa ./intercambio que es el que le pregunta a la UC
      # y escribe en el archivo buffer_Rx.txt lo que la UC le respondio.
      system("./intercambio")
      mi_archivo = 'buffer_Rx.txt'
      fh = File.open( mi_archivo , 'r' )
      #leo linea 1 (STATUS)
      @status=fh.readline
      
      #la unidad central esta adquiriendo datos (los cronometros estan corriendo)
      if @status =~ /ADQ/ then 
        #escribo variable @estado para mostrar en la vista show de partidas;
        #@estado = "Adquiriendo tiempos..."
        flash[:notice]="Adquiriendo tiempos..."
        #leo tiempos y puestos de buffer_Rx. Luego guardo en la base de datos
        read_tiempos(fh)
        @status="Adquiriendo"
        @var_puesto_nadador_1="-"
        @var_puesto_nadador_2="-"
        @var_puesto_nadador_3="-"
        @var_puesto_nadador_4="-"
        @var_puesto_nadador_5="-"
        @var_puesto_nadador_6="-"
        @var_puesto_nadador_7="-"
        @var_puesto_nadador_8="-"
        actualizo_display
        @partida.save
        puts "--ADQUIRIENDO--" 
      
      #la unidad central ya recibio el numero de laps que la mande al cargar la vista show de partidas
      #espero hasta que se presione el boton central de la unidad central (entonces paso a estado SET)  
      elsif @status =~ /PCOK/ then 
        #escribo variable @estado para mostrar en la vista show de partidas;
        #@estado="Esperando que se presione el boton COMIENZO de la Unidad Central"
        flash[:notice]="Presionar el boton COMIENZO de la Unidad Central"
        puts "--PCOK--"
        
      #la unidad central espera la senal de largada que de el juez de competencia;
      #cuando esto suceda paso a estado ADQ
      elsif @status =~ /SET/ then
        #escribo variable @estado para mostrar en la vista show de partidas 
        #@estado="Esperando orden de largada del juez de competencia"
        flash[:notice]="Esperando orden de largada del juez de competencia"
        puts "--SET--"
      
      #todos los nadadores terminaron de nadar y leo por ultima vez los tiempos y los 
      #puestos que estan en el archivo buffer_Rx
      elsif @status =~ /FIN/ then 
        #no escribo variable @estado, ya que cuando show_or_wait=true, entonces muestro
        #la leyenda "Partida ejecutada" en la vista show de partidas 
        #leo los tiempos y puestos por ultima vez, luego los guardo
        read_tiempos(fh)
        @status="Finalizado"
        @var_puesto_nadador_1=@partida.puesto_nadador_1.to_s
        @var_puesto_nadador_2=@partida.puesto_nadador_2.to_s
        @var_puesto_nadador_3=@partida.puesto_nadador_3.to_s
        @var_puesto_nadador_4=@partida.puesto_nadador_4.to_s
        @var_puesto_nadador_5=@partida.puesto_nadador_5.to_s
        @var_puesto_nadador_6=@partida.puesto_nadador_6.to_s
        @var_puesto_nadador_7=@partida.puesto_nadador_7.to_s
        @var_puesto_nadador_8=@partida.puesto_nadador_8.to_s
        actualizo_display
        #modifico show_or_wait para que no se ejecute mas esta parte del codigo
        @partida.show_or_wait=true
        @partida.comentario = params[:comentario]
        if @partida.save
        	flash[:notice]="Partida ejecutada."
		mi_archivo = 'buffer_Tx.txt'
    fhTx = File.open( mi_archivo , 'w' )
    fhTx.puts("R")
		fhTx.rewind
		fhTx.close  
      		system("./intercambio")
	end	
	puts "--FINALIZADO--"
      end 
     
      
      fh.rewind
      fh.close
  end
  
  
  
  def actualizo_display
    mi_archivo_disp = 'buffer_display.txt'
    fh_disp = File.open( mi_archivo_disp , 'w' )
    fh_disp.puts("#{@status}")
    @aux= cuentas_a_tiempo(@partida.tiempo_1)
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_1))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_2))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_3))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_4))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_5))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_6))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_7))
    fh_disp.puts(cuentas_a_tiempo(@partida.tiempo_8))
   # if @partida.nadador_2 == nil
#	    fh_disp.puts("1")
#	    fh_disp.puts("2")
#    else
	    fh_disp.puts("#{@var_puesto_nadador_1}")
	    fh_disp.puts("#{@var_puesto_nadador_2}")
 #   end
    fh_disp.puts("#{@var_puesto_nadador_3}")
    fh_disp.puts("#{@var_puesto_nadador_4}")
    fh_disp.puts("#{@var_puesto_nadador_5}")
    fh_disp.puts("#{@var_puesto_nadador_6}")
    fh_disp.puts("#{@var_puesto_nadador_7}")
    fh_disp.puts("#{@var_puesto_nadador_8}")
    fh_disp.close
  end
    
  #este metodo es llamado desde el metodo WAIT para leer desde archivo
  #buffer_Rx (se le pasa el handler del archivo), y devuelve los valores
  #en la variable de instancia @partida
  def read_tiempos (fh)
    @tiempo1 = fh.readline.to_f
    @tiempo2 = fh.readline.to_f

#corrijo tiempos 
if @tiempo1<=@tiempo2 then @dif=@tiempo2-@tiempo1 end
if @tiempo2<=@tiempo1 then @dif=@tiempo1-@tiempo2 end
if @dif<=3 then @tiempo1=@tiempo2 end
  
  
    @tiempo3 = fh.readline.to_f
    @tiempo4 = fh.readline.to_f
    @tiempo5 = fh.readline.to_f
    @tiempo6 = fh.readline.to_f
    @tiempo7 = fh.readline.to_f
    @tiempo8 = fh.readline.to_f
    #ESCRIBO variable del registro
    @partida.tiempo_1 = @tiempo1
    @partida.tiempo_2 = @tiempo2
    @partida.tiempo_3 = @tiempo3
    @partida.tiempo_4 = @tiempo4
    @partida.tiempo_5 = @tiempo5
    @partida.tiempo_6 = @tiempo6
    @partida.tiempo_7 = @tiempo7
    @partida.tiempo_8 = @tiempo8
    #LEO Y ESCRIBO PUESTOS
    if @partida.nadador_id_2==nil
	@partida.puesto_nadador_2 = fh.readline.to_i
	@partida.puesto_nadador_1 = fh.readline.to_i
    else
	@partida.puesto_nadador_1 = fh.readline.to_i 
	@partida.puesto_nadador_2 = fh.readline.to_i 
    end
    @partida.puesto_nadador_3 = fh.readline.to_i 
    @partida.puesto_nadador_4 = fh.readline.to_i 
    @partida.puesto_nadador_5 = fh.readline.to_i 
    @partida.puesto_nadador_6 = fh.readline.to_i 
    @partida.puesto_nadador_7 = fh.readline.to_i 
    @partida.puesto_nadador_8 = fh.readline.to_i 
    
  end
  
  
  #este metodo es llamado por el button_to de la vista show porque usa el metodo PUT
  #actualmente no se usa porque se guarda automaticamente cuando llega la palabra FIN 
  #en la linea de estado del archivo buffer.Rx.txt
  def update
    @partida = Partida.find(params[:id])
    @partida.show_or_wait=true
    @partida.comentario = params[:comentario]
#    @partida.comentario = "jajajajaajj"
#    @partida.update_attributes(params[:partida])
#    puts "#{params[:comentario]}"

    #leo por ultima vez el archivo y actualizo el display
    system("./intercambio")
    mi_archivo = 'buffer_Rx.txt'
    fh = File.open( mi_archivo , 'r' )
    #leo linea 1 (STATUS)
    @status=fh.readline
    read_tiempos(fh)
    @status="Finalizado"
    @var_puesto_nadador_1=@partida.puesto_nadador_1.to_s
    @var_puesto_nadador_2=@partida.puesto_nadador_2.to_s
    @var_puesto_nadador_3=@partida.puesto_nadador_3.to_s
    @var_puesto_nadador_4=@partida.puesto_nadador_4.to_s
    @var_puesto_nadador_5=@partida.puesto_nadador_5.to_s
    @var_puesto_nadador_6=@partida.puesto_nadador_6.to_s
    @var_puesto_nadador_7=@partida.puesto_nadador_7.to_s
    @var_puesto_nadador_8=@partida.puesto_nadador_8.to_s
    actualizo_display
    @partida.save
    @competencia = @partida.competencia
    flash[:success] = "La partida #{@partida.id} ha sido guardada"
    redirect_to competencia_path(@competencia)
  end


#este metodo es igual al helper print_tiempo, como no lo tomaba lo copie aca y le cambie el nombre
  def cuentas_a_tiempo (tiempo)
    if tiempo==nil
      return "00 : 00 : 000"
    end
    @sec = (tiempo/1000).to_i
    @ms = (tiempo - (@sec*1000)).to_i
    if @sec>=60
      @min = (@sec/60).to_i
      @sec = @sec-(@min*60)
      if @sec<10
        return "#{@min} : #{@sec} : #{@ms}"
      else
        return "#{@min} : #{@sec} : #{@ms}"
      end
    else
      return "00 : #{@sec} : #{@ms}"
    end  
  end

end
   
