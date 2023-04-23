module ApplicationHelper
  def title       #metodo para el titulo de la pagina
    base_title = "Chronos"
    if @title.nil?
        base_title
    else
      "#{base_title} - #{@title}"
    end
  end
  
  def print_tiempo (tiempo)
    if tiempo==nil
      return "00 : 00 : 000"
    end
    @sec = (tiempo/1000).to_i
    @ms = (tiempo - (@sec*1000)).to_i
    if @sec>=60
      @min = (@sec/60).to_i
      @sec = @sec-(@min*60)
      @aux = "#{@min} : "
      #if @sec<10
      #  @aux=
      #  return "#{@min} : #{@sec} : #{@ms}"
      #else
      #  return "#{@min} : #{@sec} : #{@ms}"
      #end
    else
      @aux="00 : "
      #return "00 : #{@sec} : #{@ms}"
    end 
    if @sec<10
      @aux=@aux+"0#{@sec} : "
    else
      @aux = @aux + "#{@sec} : "
    end
    if @ms<10 
      @aux = @aux + "00#{@ms}"  
      return @aux
    elsif @ms<100
      @aux = @aux + "0#{@ms}" 
      return @aux
    else  
      @aux = @aux + "#{@ms}"
    end
  end
  
    
end
